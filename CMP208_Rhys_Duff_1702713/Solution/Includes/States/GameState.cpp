#include "pch.h"
#include "GameState.h"

#include "Context.h"

GameState::GameState(gef::Platform* platform_)
{
	

}

GameState::~GameState()
{

	CleanModels();
	CleanUpFont();

	delete world;
	world = nullptr;
}

void GameState::OnEnter()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = context->Renderer()->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.45f, 0.25f, 0.45f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);

	// initialise primitive builder
	primitive_builder_ = new PrimitiveBuilder(*context->GetPlatform());

	b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
	world = new b2World(gravity);

	InitPlayer();
	InitScene();
	InitInput();

	t_camera = ThirdPersonCamera::Create(context->GetPlatform());
	t_camera->InitialisePerspectiveMatrices();

	InitFont();
	SetupLights();

	//Set the collision callback methods.
	world->SetContactListener(&scene_contact_listener);

}

void GameState::Input(float delta_time)
{
	
	
	this->context->GetInput()->PosessPawn(static_cast<AnimatedPawn*>(essential_anim_objects[0]));

	//Process Input
	Player* player = static_cast<Player*>(essential_anim_objects[0]);
	player->BroadcastInput(false);
	this->context->GetInput()->ProcessInput(delta_time);



	if (this->context->GetInput()->GetInputManager()->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_ESCAPE))
	{
		context->Transition(States::PAUSE);
	}
	
}

bool GameState::Update(float delta_time)
{

		////////////////////////////////////////////////////////////////////////////////////

		t_camera->SetTarget(essential_anim_objects[0]->GetPosition());
		t_camera->Update(delta_time);
		//
		////////////////////////////////////////////////////////////////////////////////////
	
		////////////////////////////////////////////////////////////////////////////////////
		//Game Logic.
	
		for (auto& object : essential_objects)
		{
			object->Update(delta_time);
		}
	
		for (auto& anim_object : essential_anim_objects)
		{
			anim_object->AnimationUpdate(delta_time);
			anim_object->Update(delta_time);
		}

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


		return true;
}

void GameState::Render()
{
	gef::Renderer3D* renderer = this->context->Renderer();
	gef::SpriteRenderer* sprite_renderer = this->context->SpriteRenderer();


	// projection
	t_camera->SetSceneMatrices(renderer);

	// draw 3d geometry
	renderer->Begin();

	
	for (auto& object : essential_objects)
	{
		renderer->DrawMesh(*object);
	}

	for (auto& object : essential_anim_objects)
	{
		renderer->DrawSkinnedMesh(*object, object->bone_matrices());
	}

	renderer->End();


	// start drawing sprites, don't clear the frame buffer
	sprite_renderer->Begin(false);
	
		DrawHUD(sprite_renderer);

	sprite_renderer->End();
}

void GameState::OnExit()
{
}

void GameState::InitFont()
{
	font_ = new gef::Font(*platform);
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

}

void GameState::InitPlayer()
{
	AssetLoader* asset_loader = context->GetAssetLoader();

	gef::Scene* scn_ = asset_loader->LoadSceneAssets(platform, "../assets/Robot/robot.scn");

	//Sort out model loading, streamline it.
	Player* player = Player::Create(*asset_loader->LoadSkeleton(scn_), *platform, world);

	player->asset = scn_;
	player->SetPosition(6.0f, 0.0f, 0.0f);
	player->SetRotation(0.0f, 90.0f, 0.0f);
	player->SetScale(1.0f, 1.0f, 1.0f);
	player->SetObjectType(ObjectType::dynamic_pawn_);
	player->set_mesh(asset_loader->LoadMesh(scn_));
	player->idle = asset_loader->LoadAnimation("../assets/Robot/Animation/@idle01.scn", "");
	player->walk = asset_loader->LoadAnimation("../assets/Robot/Animation/@walk.scn", "");

	if (player->idle)
	{
		player->AnimationPlayer()->set_clip(player->idle);
		player->AnimationPlayer()->set_anim_time(0.0f);
		player->AnimationPlayer()->set_looping(true);
	}

	essential_anim_objects.push_back(player);


}

void GameState::InitScene()
{
		/*
		//Planet
		
		Planet* planet = Planet::Create(*platform, world, 1.0f);
		planet->SetPosition(0.0f, -0.5f, 0.0f);
		planet->SetScale(1.0f, 1.0f, 1.0f);
	
		planet->set_mesh(asset_loader->LoadMesh("world.scn"));
		planet->AttachPhysicsComponent(world);
		planet->InitialisePhysicsFixture(PhysicsComponent::Shape::CIRCLE,
			0.0f,
			1.0f,
			1.0f,
			false);

		essential_objects.push_back(planet);
		*/
}

void GameState::InitInput()
{
	//Now controls the player.
	
}

void GameState::LoadSceneModels()
{
//	GameObject* tracer_bike = GameObject::Create(*platform);
//
//	tracer_bike->SetMesh(asset_loader->LoadMesh("../assets/Ships/Tracer/tracer.scn"));
//	tracer_bike->SetPosition(0.0f, 0.0f, 0.0f);
//	tracer_bike->SetObjectType(ObjectType::static_);
//	tracer_bike->SetScale(1.0f, 1.0f, 1.0f);
//	essential_objects.push_back(tracer_bike);

	AssetLoader* asset_loader = context->GetAssetLoader();

	GameObject* town = GameObject::Create(*platform);
	town->SetObjectType(ObjectType::static_);
	town->SetPosition(0.0f, 0.0f, 8.0f);
	town->SetMesh(asset_loader->LoadMesh("..assets/Structures/town_block_a.scn"));
	town->SetScale(1.0f, 1.0f, 1.0f);
	essential_objects.push_back(town);

	gef::Scene* scn_ = asset_loader->LoadSceneAssets(platform, "..assets/Structures/cloud_a.scn");

	for (int i = 0; i < 12; ++i)
	{
		GameObject* cloud = GameObject::Create(*platform);
		cloud->SetMesh(asset_loader->LoadMesh(scn_));
		cloud->SetPosition(rand() % 0 + 10, 4.0f, rand() % -2 + 9);
		cloud->SetScale(1.0f, 1.0f, 1.0f);
		essential_objects.push_back(cloud);
	}

	

}

void GameState::CleanModels()
{

}
