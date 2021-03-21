#include "pch.h"
#include "GameState.h"

GameState::GameState(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, gef::InputManager* input_)
	:
	platform(platform_),
	renderer(renderer_),
	sprite_renderer(sprite_renderer_),
	input_manager(input_)
{

	b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
	world = new b2World(gravity);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(*platform_);

	InitPlayer();
	InitScene();
	InitInput();

	//camera

	t_camera = ThirdPersonCamera::Create(platform_);
	t_camera->InitialisePerspectiveMatrices();

	InitFont();
	SetupLights();

	//Set the collision callback methods.
	world->SetContactListener(&scene_contact_listener);

	//button = UIButton::Create(platform_, std::string("Start"), gef::Vector2(200.0f, 200.0f));
}

GameState::~GameState()
{
}

void GameState::OnEnter()
{
	gef::DebugOut("This is the Game state\n");
}

void GameState::Input(float delta_time)
{
}

void GameState::Update(float delta_time)
{

		////////////////////////////////////////////////////////////////////////////////////
		//Process Input
		pawn_controller->ProcessInput(delta_time);
		pawn_controller->ControlCamera(camera, delta_time);
	
		t_camera->FocusOnObject(player);
		t_camera->Update(delta_time);
		//
		////////////////////////////////////////////////////////////////////////////////////
	
			////////////////////////////////////////////////////////////////////////////////////
		//Game Logic.
	
		/*..Player update..*/
		floor->Update(delta_time);
		player->Update(delta_time);
		//planet->Update(delta_time);
	
		//button->Update(delta_time);
	
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

}

void GameState::Render()
{
	// projection
	t_camera->SetSceneMatrices(renderer);

	// draw 3d geometry
	renderer->Begin();


	floor->Render(renderer);

	//planet->Render(renderer_3d_);
	player->Render(renderer);


	renderer->End();


	// start drawing sprites, don't clear the frame buffer
	sprite_renderer->Begin(false);
	//button->Render(sprite_renderer);
	DrawHUD();
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
}

void GameState::DrawHUD()
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

void GameState::InitPlayer()
{
	// setup the mesh for the player - Note: No need to call seperate functions to instantiate mesh and physics.
	player = Pawn::Create(*platform, world);
	player->SetPosition(0.0f, 4.0f, 0.0f);
	player->SetScale(1.0f, 1.0f, 1.0f);
	player->SetObjectType(ObjectType::dynamic_pawn_);
	player->SetMeshFromDisc(primitive_builder_, std::string("rocket.scn"));

	/*..Attach a physics component to the object..*/
	player->AttachPhysicsComponent(world);

	player->InitialisePhysicsFixture(PhysicsComponent::Shape::BOX,
		0.4f, //Density
		0.5f, //Friction
		1.0f, //Mass
		false //Is trigger
	);
}

void GameState::InitScene()
{
		//Floor
		floor = GameObject::Create(*platform, world, false);
		floor->SetObjectType(ObjectType::environment_);
		floor->SetPosition(0.0f, -2.0f, 0.0f);
		floor->SetScale(10.0f, 1.0f, 1.0f);
		floor->SetMeshAsCube(primitive_builder_);
		floor->AttachPhysicsComponent(world);
	
		floor->InitialisePhysicsFixture(PhysicsComponent::Shape::BOX,
			0.0f, //Density
			1.0f, //Friction
			0.5,  //Mass
			false //Is trigger
		);

	//	//Planet
	//	planet = Planet::Create(platform_, world, 1.0f);
	//	planet->SetPosition(0.0f, -4.0f, 0.0f);
	//	//planet->SetScale(10.0f, 10.0f, 10.0f);
	//
	//	planet->AttachPhysicsComponent(world);
	//
	//	planet->SetMeshAsSphere(primitive_builder_);
	//
	//	planet->InitialisePhysicsFixture(PhysicsComponent::Shape::CIRCLE,
	//		0.0f,
	//		1.0f,
	//		1.0f,
	//		false);
}

void GameState::InitInput()
{
	//input 
	pawn_controller = PawnController::Create(*platform);
	pawn_controller->SetPointerToInputManagers(input_manager);

	//Now controls the player.
	pawn_controller->PosessPawn(player);
}
