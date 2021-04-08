#include "pch.h"
#include "GameState.h"

#include "Context.h"

GameState::GameState(gef::Platform* platform_, GraphicsData* asset_loader)
	:
	player(nullptr),
	world(nullptr),
	level(nullptr)
{
	font_ = nullptr;
	renderer = gef::Renderer3D::Create(*platform_);
}

GameState::~GameState()
{
	//Kill the font.
	CleanUpFont();

	if (player) {
		delete player;
		player = nullptr;
	}
	if (world) {
		delete world;
		world = nullptr;
	}
}

void GameState::OnEnter()
{
	gef::Platform* platform = context->GetPlatform();
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();

	//Physics & Player.
	InitialiseScene();
	//Lighting
	SetupLights();
	//Audio
	LoadLevelSoundEffects();
	//Font
	InitFont();
	//Camera
	InitCamera();
	//Skybox
	InitSkybox();
	//Set the collision callback methods.
	world->SetContactListener(&scene_contact_listener);
	//Posses the player's physics body.
	context->GetInput()->PossessPhysObject(player_phys);
}

void GameState::Input(float delta_time)
{
	PawnController* input = context->GetInput();

	//Update input devices.
	input->GetInputManager()->Update();
	


	gef::Keyboard* keyboard = input->GetInputManager()->keyboard();

	if (keyboard->IsKeyPressed(gef::Keyboard::KeyCode::KC_ESCAPE))
	{
		context->Transition(States::PAUSE);
	}

	//Process Input
	player->BroadcastInput(false);
	input->ProcessInput(delta_time);
}

bool GameState::Update(float delta_time)
{

		////////////////////////////////////////////////////////////////////////////////////
		//
		if (t_camera != nullptr)
		{
			t_camera->SetTarget(player->GetPosition());
			t_camera->Update(delta_time);
		}
		//
		////////////////////////////////////////////////////////////////////////////////////
	
		////////////////////////////////////////////////////////////////////////////////////
		//Game Logic.

		//Audio
		//context->GetAudio3D()->listener().SetTransform(player->transform());
		//context->GetAudio3D()->Update();

		//For each partition - update the gameobjects and it's physics component.
		UpdateLevel(delta_time);

		//Update the scenes game objects and their respective physics bodies.
		for (int index = 0; index < environment_objects.size(); ++index)
		{
			if (environment_objects.at(index) != nullptr)
			{
				physics_components.at(index)->Update();

				environment_objects.at(index)->Update(delta_time, physics_components.at(index));
			}
		}
	

		//Update the player.
		if (player != nullptr)
		{
			player->Update(delta_time, player_phys);
		}

		skybox->SetPosition(player->GetPosition().x(), player->GetPosition().y(), player->GetPosition().z());
		skybox->Update(delta_time);

		
		//End Game Logic.
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		//Physics Step.
	
		const uint32 velocity_iterations = 8;
		const uint32 position_iterations = 4;
	
		/*
		*
		*	Update the physics world, iteration variables dictate the quality of the simulations.
		*
		*	Collisions are handled here through callback methods.
		*
		*/
		world->Step(delta_time, velocity_iterations, position_iterations);
	
		//End Physics Step.
		////////////////////////////////////////////////////////////////////////////////////

		//If the player has fallen of the world end the game.
		if (player && player->GetPosition().y() < -2.0f)
		{
			context->Reset(true);
			context->Transition(States::DEATH);
		}

		return true;
}

void GameState::Render()
{
	gef::SpriteRenderer* sprite_renderer = this->context->SpriteRenderer();


	//Set the correct view matrices for our camera.
	t_camera->SetSceneMatrices(renderer);

	// Being rendering all of our 3D geometry.
	renderer->Begin();

	//Draw the gfx contained in a chunk.
	if (level != nullptr)
	{
		for (auto& chunk : level->chunks)
		{
			for (int j = 0; j < chunk->game_objects.size(); ++j)
			{
				if (chunk->game_objects[j] != nullptr)
				{
					renderer->DrawMesh(*chunk->game_objects[j]);
				}
			}
		}
	}

	for (auto& object : environment_objects)
	{
		if (object != nullptr)
		{
			renderer->DrawMesh(*object);
		}
		
	}

	if(player != nullptr)
	renderer->DrawSkinnedMesh(*player, player->bone_matrices());

	//End rendering.
	renderer->End();


	// start drawing sprites, don't clear the frame buffer
	sprite_renderer->Begin(false);
	
		DrawHUD(sprite_renderer);

	sprite_renderer->End();
}

void GameState::OnExit()
{
	// Clean up shaders.
	renderer->default_shader_data().CleanUp();

	delete font_;
	font_ = nullptr;


	ResetScene();
}

void GameState::InitFont()
{
	font_ = new gef::Font(*context->GetPlatform());
	font_->Load("comic_sans");
}

void GameState::CleanUpFont()
{
	if (font_ != nullptr)
	{
		delete font_;
		font_ = nullptr;
	}
}

void GameState::DrawHUD(gef::SpriteRenderer* sprite_renderer)
{
	float x = t_camera->CameraLookAt().x();
	float y = t_camera->CameraLookAt().y();
	float z = t_camera->CameraLookAt().z();

	if (font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer,
			gef::Vector4(200.0f, 510.0f, -0.9f),
			1.0f, 0xffffffff, gef::TJ_LEFT,
			"Camera Target: %.1f %.1f %.1f",
			x,
			y,
			z
		);
	}
}

void GameState::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer->default_shader_data();
	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));
	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void GameState::InitialiseScene()
{
	gef::Platform* platform = context->GetPlatform();
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();

	if (context->IsReset())
	{
		b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
		world = new b2World(gravity);

		primitive_builder_ = new PrimitiveBuilder(*platform);

		InitPlayer(platform);

		//Set the collision callback methods.
		world->SetContactListener(&scene_contact_listener);

		//level = new LevelGenerator(platform);
		//level->GenerateWorld();
		//level->GenerateWorldPlatforms(primitive_builder_, world);

	
		GameObject* ground = GameObject::Create(*platform);
		ground->SetMeshAsCube(primitive_builder_);
		ground->SetObjectType(ObjectType::environment_);
		ground->SetPosition(0.0f, -2, 0.0f);
		ground->SetScale(100.0f, 1.0f, 2.0f);
		environment_objects.push_back(ground);

		// Physics body.
		PhysicsComponent* ground_body = PhysicsComponent::Create(world, ground, false);
		ground_body->CreateFixture(PhysicsComponent::Shape::BOX, 0.0f, 0.1f, 1.0f, false);
		physics_components.push_back(ground_body);

		//Avoiding memory leaks.
		//Only Transitioning to the main menu 
		//Resets the data.
		context->Reset(false);
	}
}

void GameState::InitSkybox()
{
	gef::Platform* platform = context->GetPlatform();
	skybox = GameObject::Create(*context->GetPlatform());
	skybox->SetPosition(0.0f, 0.0f, 0.0f);
	skybox->SetScale(10.0f, 10.0f, 10.0f);


	//gef::Scene* scn_ = context->GetAssetLoader()->LoadSceneAssets(platform, "../assets/skybox.scn");
	context->GFXData()->GetAssetLoader()->LoadMesh("../assets/skybox.scn");
}

void GameState::InitCamera()
{
	//Setup the camera.
	t_camera = ThirdPersonCamera::Create(context->GetPlatform());
	t_camera->InitialisePerspectiveMatrices();

}

void GameState::ResetScene()
{
	// @note If context is nullptr then we haven't transitioned to this state
	if (context->IsReset())
	{
		delete level;
		level = nullptr;

		delete t_camera;
		t_camera = nullptr;

		delete player;
		player = nullptr;

		delete player_phys;
		player_phys = nullptr;

		delete primitive_builder_;
		primitive_builder_ = nullptr;

		if (skybox)
		{
			delete skybox;
			skybox = nullptr;
		}

		for (auto& enviro : environment_objects)
		{
			delete enviro;
			enviro = nullptr;
		}

		for (auto& physics : physics_components)
		{
			delete physics;
			physics = nullptr;
		}

		renderer->default_shader_data().CleanUp();
	}
	CleanUpFont();
}

void GameState::UpdateLevel(float delta_time)
{
	if (level != nullptr)
	{
		for (auto& chunk : level->chunks)
		{
			for (int j = 0; j < chunk->game_objects.size(); ++j)
			{
				//Ensure we're not dealing with a NULL object - there are some.
				if (chunk->game_objects.at(j) != nullptr)
				{
					if (chunk->phys_components.at(j) != nullptr)
					{
						//Update the chunks.
						chunk->phys_components.at(j)->Update();

						//Get the physics component for better readability.
						PhysicsComponent* phys_component = chunk->phys_components.at(j);
						chunk->game_objects.at(j)->Update(delta_time, phys_component);
					}
				}
			}
		}
	}
}

void GameState::InitPlayer(gef::Platform* platform)
{
	//Create pointers to the asset_loader and graphics data class.
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();
	GraphicsData* gfx_data = context->GFXData();

	/*..Create our player..*/
	player = Player::Create(*asset_loader->LoadSkeleton("../assets/Robot/robot.scn"), *platform);
	/*..Store our mesh in the data class..*/
	gfx_data->InsertModel(ModelID::Player, asset_loader->LoadMesh("../assets/Robot/robot.scn"));
	/*..Using the player ID assign a pointer to the mesh..*/
	player->set_mesh(gfx_data->GetMesh(ModelID::Player));

	player->SetPosition(0.0f, 2.0f, 0.0f);
	player->SetRotation(0.0f, 90.0f, 0.0f);
	player->SetScale(1.0f, 1.0f, 1.0f);

	player->SetObjectType(ObjectType::dynamic_pawn_);
	player->idle = asset_loader->LoadAnimation("../assets/Robot/Animation/@idle01.scn", "");
	player->walk = asset_loader->LoadAnimation("../assets/Robot/Animation/@walk.scn", "");

	if (player->idle)
	{
		player->AnimationPlayer()->set_clip(player->idle);
		player->AnimationPlayer()->set_anim_time(0.0f);
		player->AnimationPlayer()->set_looping(true);
	}

	player_phys = PhysicsComponent::Create(world, player, true);
	player_phys->CreateFixture(PhysicsComponent::Shape::BOX, 0.3f, 0.4f, 0.5f, false);
}


void GameState::LoadLevelSoundEffects()
{
	//Load SFX
}

void GameState::LoadSceneModels(AssetLoader* asset_loader, gef::Platform* platform)
{
	//Load Scene
}

