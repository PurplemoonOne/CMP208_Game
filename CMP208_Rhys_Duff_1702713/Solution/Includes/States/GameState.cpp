#include "pch.h"
#include "GameState.h"

#include "Context.h"
#include "system/platform.h"

/*..Level Generator..*/
#include "LevelGenerator.h"
#include "ParallaxBackground.h"

GameState::GameState(gef::Platform* platform_, GraphicsData* asset_loader)
	:
	player(nullptr),
	skybox(nullptr),
	world(nullptr),
	level(nullptr),
	primitive_builder_(nullptr),
	t_camera(nullptr),
	time(nullptr),
	font(nullptr),
	user_interface(nullptr),
	fps_(0.0f),
	timer(0.0f)
{
	/*..Create a new 3D renderer..*/
	renderer = gef::Renderer3D::Create(*platform_);
}

GameState::~GameState()
{
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

	/*..Load the models from disc..*/
	context->GFXData()->LoadModels();
	context->GetAudio()->PlayMusic(MusicID::LEVEL);

	//Fonts
	InitFont();

	//Physics & Player.
	InitialiseScene();

	//Lighting
	SetupLights();

	//Camera
	InitCamera();

	//Set the collision callback methods.
	world->SetContactListener(&scene_contact_listener);

	//Posses the player's physics body.
	context->GetInput()->PosessPawn(player);
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
		context->GetAudio()->GetAudio3D()->listener().SetTransform(player->transform());
		context->GetAudio()->GetAudio3D()->Update();

		//For each partition - update the gameobjects and it's physics component.
		// 
		// 
		skybox->SetPosition(player->GetPosition().x(), player->GetPosition().y(), player->GetPosition().z());
		skybox->Update(delta_time);

		//level->Update(delta_time);
		level->EvaluateChunkToRender(player->GetPosition(), true);
		level->UpdateChunk(delta_time);
		UpdatePlayer(delta_time);

		//End Game Logic.
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		//Physics Step.
	
		const uint32 velocity_iterations = 4;
		const uint32 position_iterations = 2;
	
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
	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	//Set the correct view matrices for our camera.
	t_camera->SetSceneMatrices(renderer);

	// Being rendering all of our 3D geometry.
	renderer->Begin(true);
	RenderSkysphere(renderer);

		if (player != nullptr)
		{
			renderer->DrawSkinnedMesh(*player, player->bone_matrices());
		}

		//Draw the gfx contained in a chunk.
		//level->Render(renderer);
		level->RenderChunk(renderer);

	//End rendering.
	renderer->End();


	// start drawing sprites, don't clear the frame buffer
	sprite_renderer->Begin(false);

	user_interface->DrawScore(sprite_renderer, player->GetScore());
	user_interface->DrawHealth(sprite_renderer, player->GetHealth());

	sprite_renderer->End();
}

void GameState::OnExit()
{
	// Clean up shaders.
	renderer->default_shader_data().CleanUp();
	context->GetAudio()->PlayMusic(MusicID::null);

	if (font)
	{
		delete font;
		font = nullptr;
	}
	if (time)
	{
		delete time;
		time = nullptr;
	}
	if (health)
	{
		delete health;
		health = nullptr;
	}

	ResetScene();
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

		//Skybox
		InitSkybox();
	
		//Set the collision callback methods.
		world->SetContactListener(&scene_contact_listener);

		level = new LevelGenerator(context, world);

		user_interface = UserInterface::Create(context->GFXData());
		user_interface->InitFont(context->GetPlatform());
		//Avoiding memory leaks.
		//Only Transitioning to the main menu 
		//Resets the data.
		context->Reset(false);
	}
}

void GameState::InitSkybox()
{
	skybox = Skybox::Create();
	skybox->SetMesh(context->GFXData()->GetMesh(ModelID::SkySphere));
	skybox->SetObjectType(ObjectType::environment_dynamic_);
	skybox->SetPosition(player->GetPosition().x(), player->GetPosition().y(), player->GetPosition().z());
	skybox->SetScale(20.0f, 20.0f, 20.0f);
	skybox->SetAlive(true);
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
		//Clean up models if system reset.
		context->GFXData()->ClearMesh();

		delete level;
		level = nullptr;

		delete t_camera;
		t_camera = nullptr;

		delete player;
		player = nullptr;

		delete primitive_builder_;
		primitive_builder_ = nullptr;


		if (skybox)
		{
			delete skybox;
			skybox = nullptr;
		}

		renderer->default_shader_data().CleanUp();
	}

}



void GameState::DrawHUD()
{
	if (font)
	{
		font->RenderText(
			context->SpriteRenderer(),
			gef::Vector4(500.0f, 250.0f, -0.9f),
			1.0f,
			0xffffffff,
			gef::TextJustification::TJ_LEFT,
			"Score : %.1f",
			player->GetScore()
		);
	}

	if (health)
	{
		health->RenderText(
			context->SpriteRenderer(),
			gef::Vector4(100.0f, 250.0f, -0.9f),
			1.0f,
			0xffffffff,
			gef::TextJustification::TJ_LEFT,
			"Health : %.1f",
			player->GetHealth()
		);
	}

	if (time)
	{
		time->RenderText(
			context->SpriteRenderer(),
			gef::Vector4(
				(context->GetPlatform()->width() / 2.0f),
				(context->GetPlatform()->height() / 6.0f),
				-0.9f),
			1.0f,
			0xffffffff,
			gef::TextJustification::TJ_LEFT,
			"Time Remaining : %.1f",
			timer

		);
	}
}

void GameState::RenderSkysphere(gef::Renderer3D* renderer)
{
	renderer->SetDepthTest(gef::Renderer3D::DepthTest::kAlways);
	renderer->DrawMesh(*skybox);
	renderer->SetDepthTest(gef::Renderer3D::DepthTest::kLessEqual);
}

void GameState::UpdatePlayer(float delta_time)
{
	//Update the player.
	if (player != nullptr)
	{
		player->Update(delta_time);
		user_interface->Update(context->GetPlatform());


		//Update score.
		WinLoseScreen* wl = nullptr;

		//Cast to winloss screen.
		wl = static_cast<WinLoseScreen*>(this->context->GetState(States::DEATH));

		if (wl != nullptr) 
		{
			wl->GetFinalScore(player->GetScore());
		}

		if (player->ReachedPortal())
		{
			context->SetHasWon(true);
			context->Reset(true);
			context->SetHasWon(true);
			context->Transition(States::DEATH);
		}
	}

	if (player != nullptr)
	{
		//If the player has fallen of the world end the game.
		if (player->GetPosition().y() < -2.0f)
		{
			context->Reset(true);
			context->SetHasWon(false);
			context->Transition(States::DEATH);
		}
	}
}

void GameState::InitPlayer(gef::Platform* platform)
{
	//Create pointers to the asset_loader and graphics data class.
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();
	GraphicsData* gfx_data = context->GFXData();

	/*..Create our player..*/
	player = Player::Create(*asset_loader->LoadSkeleton("../assets/Robot/robot.scn"));
	/*..Using the player ID assign a pointer to the mesh..*/
	player->set_mesh(gfx_data->GetMesh(ModelID::Player));				//Grab mesh from data class.
	player->IgnoreZRotation(true);										//Ignore Z rotation, box2D will not influence Z rotation.
	player->SetPosition(10.0f, 25.0f, 10.0f);							//Set Position
	player->SetRotation(0.0f, 90.0f, 0.0f);								//Set Rotation
	player->SetScale(1.0f, 1.0f, 1.0f);									//Set Scale
	player->SetObjectType(ObjectType::dynamic_pawn_);					//Object type

	player->InsertAnimation(AnimationID::idle, asset_loader->LoadAnimation("../assets/Robot/Animation/@idle01.scn", ""));
	player->InsertAnimation(AnimationID::walk, asset_loader->LoadAnimation("../assets/Robot/Animation/@walk.scn", ""));
	player->InsertAnimation(AnimationID::run, asset_loader->LoadAnimation("../assets/Robot/Animation/@run.scn", ""));
	player->InsertAnimation(AnimationID::jump, asset_loader->LoadAnimation("../assets/Robot/Animation/@jump.scn", ""));
	player->InsertAnimation(AnimationID::fall, asset_loader->LoadAnimation("../assets/Robot/Animation/@fall.scn", ""));
	player->InsertAnimation(AnimationID::fall_to_roll, asset_loader->LoadAnimation("../assets/Robot/Animation/@fall_roll.scn", ""));


	if (player->GetAnimation(AnimationID::idle))
	{
		player->AnimationPlayer()->set_clip(player->GetAnimation(AnimationID::idle));
		player->AnimationPlayer()->set_anim_time(0.0f);
		player->AnimationPlayer()->set_looping(true);
	}

	/*..Create the physics body for the player..*/
	player->AttachPhysicsComponent(world);
	player->InitialisePhysicsFixture(PhysicsComponent::Shape::BOX, 0.4f, 0.6f, 1.0f, false);
}


void GameState::InitFont()
{
	gef::Platform* platform = context->GetPlatform();

	font = new gef::Font(*platform);
	font->Load("comic_sans");

	health = new gef::Font(*platform);
	health->Load("comic_sans");

	time = new gef::Font(*platform);
	time->Load("comic_sans");
}

