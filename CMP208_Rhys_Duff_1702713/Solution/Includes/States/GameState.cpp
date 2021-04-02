#include "pch.h"
#include "GameState.h"

#include "Context.h"

GameState::GameState(gef::Platform* platform_, AssetLoader* asset_loader)
{
	b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
	world = new b2World(gravity);

	// initialise primitive builder
	primitive_builder_ = new PrimitiveBuilder(*platform_);

	InitInput();
	InitPlayer(asset_loader, platform_);
	InitScene(asset_loader, platform_);

	//Set the collision callback methods.
	world->SetContactListener(&scene_contact_listener);

	delete primitive_builder_;
	primitive_builder_ = nullptr;
}

GameState::~GameState()
{

	CleanModels();
	CleanUpFont();

	if(world != nullptr)
	delete world;
	world = nullptr;
}

void GameState::OnEnter()
{
	// initialise primitive builder
	primitive_builder_ = new PrimitiveBuilder(*context->GetPlatform());

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

	InitAudio();
	InitFont();

	context->GetInput()->PosessPawn(static_cast<AnimatedPawn*>(player));

	t_camera = ThirdPersonCamera::Create(context->GetPlatform());
	t_camera->InitialisePerspectiveMatrices();
}

void GameState::Input(float delta_time)
{
	PawnController* input = this->context->GetInput();

	input->GetInputManager()->Update();
	



	gef::Keyboard* keyboard = input->GetInputManager()->keyboard();

	if (keyboard && keyboard->IsKeyPressed(gef::Keyboard::KeyCode::KC_ESCAPE))
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

		t_camera->SetTarget(player->GetPosition());
		t_camera->Update(delta_time);
		//
		////////////////////////////////////////////////////////////////////////////////////
	
		////////////////////////////////////////////////////////////////////////////////////
		//Game Logic.

		//Audio
		context->GetAudio3D()->listener().SetTransform(player->transform());
		context->GetAudio3D()->Update();


		//Update the scenes game objects and their respective physics bodies.
		for (int index = 0; index < environment_objects.size(); ++index)
		{
			physics_components.at(index)->Update();

			environment_objects.at(index)->Update(delta_time);
		}
	

		//Update the player.
		player->AnimationUpdate(delta_time);
		player->UpdateMesh(player_phys);
		player->Update(delta_time);
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

	
	for (auto& object : environment_objects)
	{
		renderer->DrawMesh(*object);
	}

	renderer->DrawSkinnedMesh(*player, player->bone_matrices());


	renderer->End();


	// start drawing sprites, don't clear the frame buffer
	sprite_renderer->Begin(false);
	
		DrawHUD(sprite_renderer);

	sprite_renderer->End();
}

void GameState::OnExit()
{
	delete font_;
	font_ = nullptr;

	delete primitive_builder_;
	primitive_builder_ = nullptr;
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

}

void GameState::InitPlayer(AssetLoader* asset_loader, gef::Platform* platform)
{
	gef::Scene* scn_ = asset_loader->LoadSceneAssets(platform, "../assets/Robot/robot.scn");

	//Sort out model loading, streamline it.
	player = Player::Create(*asset_loader->LoadSkeleton(scn_), *platform);

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


}

void GameState::InitScene(AssetLoader* asset_loader, gef::Platform* platform)
{
	GameObject* ground = GameObject::Create(*platform);
	ground->SetPosition(0.0f, -1.0f, 0.0f);
	ground->SetScale(10.0f, 1.0f, 10.0f);

	environment_objects.push_back(ground);

	PhysicsComponent* ground_body = PhysicsComponent::Create(world, ground, false);
	ground_body->CreateFixture(PhysicsComponent::Shape::BOX, 0.0f, 0.1f, 1.0f, false);
	
	physics_components.push_back(ground_body);

}

void GameState::InitInput()
{



}

void GameState::InitAudio()
{
	UInt32 id = context->AudioManager()->LoadSample("box_collected.wav", *context->GetPlatform());

	AudioEmitter audio_emitter;
	audio_emitter.Init(id, true);

	audio_emitter.set_position(gef::Vector4(5.5f, 0.0f, 0.0f));
	audio_emitter.set_radius(100.0f);

	context->GetAudio3D()->AddEmitter(audio_emitter);
}

void GameState::LoadSceneModels(AssetLoader* asset_loader, gef::Platform* platform)
{
//	GameObject* tracer_bike = GameObject::Create(*platform);
//
//	tracer_bike->SetMesh(asset_loader->LoadMesh("../assets/Ships/Tracer/tracer.scn"));
//	tracer_bike->SetPosition(0.0f, 0.0f, 0.0f);
//	tracer_bike->SetObjectType(ObjectType::static_);
//	tracer_bike->SetScale(1.0f, 1.0f, 1.0f);
//	essential_objects.push_back(tracer_bike);

	GameObject* town = GameObject::Create(*platform);
	town->SetObjectType(ObjectType::static_);
	town->SetPosition(0.0f, 0.0f, 8.0f);
	town->SetMesh(asset_loader->LoadMesh("..assets/Structures/town_block_a.scn"));
	town->SetScale(1.0f, 1.0f, 1.0f);
	environment_objects.push_back(town);

	gef::Scene* scn_ = asset_loader->LoadSceneAssets(platform, "..assets/Structures/cloud_a.scn");

	for (int i = 0; i < 12; ++i)
	{
		GameObject* cloud = GameObject::Create(*platform);
		cloud->SetMesh(asset_loader->LoadMesh(scn_));
		cloud->SetPosition(rand() % 0 + 10, 4.0f, rand() % -2 + 9);
		cloud->SetScale(1.0f, 1.0f, 1.0f);
		environment_objects.push_back(cloud);
	}

	

}

void GameState::CleanModels()
{

}
