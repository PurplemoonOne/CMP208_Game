#include "pch.h"

#include "scene_app.h"
#include <system/platform.h>

//Graphics includes
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>

//Scene
#include "graphics/scene.h"

//Multi-Threading
#include <thread>
#include <mutex>

//Import from the thread and mutex libraries.
using std::thread;
using std::mutex;
using std::unique_lock;

//Maths
#include <maths/math_utils.h>

//Other headers
#include "PawnController.h"

//Debug
#include <system/debug_log.h>


SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL)
{

	/*..Initialise 2D world..*/
	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);

}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	InitPlayer();
	InitScene();
	InitInput();

	//camera
	//camera = Camera::Create(&platform_);
	//camera->InitialisePerspectiveMatrices();
	t_camera = ThirdPersonCamera::Create(&platform_);
	t_camera->InitialisePerspectiveMatrices();

	InitFont();
	SetupLights();

	//Set the collision callback methods.
	world->SetContactListener(&scene_contact_listener);
}

void SceneApp::CleanUp()
{
	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete player;
	player = nullptr;

	//delete camera;
	//camera = nullptr;

	delete t_camera;
	t_camera = nullptr;

	delete input;
	input = nullptr;

	/*..Clean up 2D physics world..*/
	delete world;
	world = nullptr;
}


bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	////////////////////////////////////////////////////////////////////////////////////
	//Process Input
	input->ProcessInput(frame_time);
	input->ControlCamera(camera, frame_time);
	
	t_camera->FocusOnObject(player);
	t_camera->Update(frame_time);
	//
	////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////
	//Game Logic.

	/*..Player update..*/
	//floor->Update(frame_time);
	player->Update(frame_time);
	//planet->Update(frame_time);


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
			world->Step(frame_time, velocity_iterations, position_iterations);
			
	//End Physics Step.
	////////////////////////////////////////////////////////////////////////////////////


	return true;
}

void SceneApp::Render()
{
	// projection
	t_camera->SetSceneMatrices(renderer_3d_);

	// draw 3d geometry
	renderer_3d_->Begin();

	
		//floor->Render(renderer_3d_);
		
		//planet->Render(renderer_3d_);
		player->Render(renderer_3d_);


	renderer_3d_->End();


	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	DrawHUD();
	sprite_renderer_->End();
}
void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::DrawHUD()
{
	float x = t_camera->CameraLookAt().x();
	float y = t_camera->CameraLookAt().y();
	float z = t_camera->CameraLookAt().z();

	if(font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_,
			gef::Vector4(200.0f, 510.0f, -0.9f),
			1.0f, 0xffffffff, gef::TJ_LEFT,
			"Camera Target: %.1f %.1f %.1f",
			x,
			y,
			z
		);
	}
}

void SceneApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void SceneApp::InitPlayer()
{
	// setup the mesh for the player - Note: No need to call seperate functions to instantiate mesh and physics.
	player = Pawn::Create(platform_, world);
	player->SetPosition(0.0f, 4.0f, 0.0f);
	player->SetScale(1.0f, 1.0f, 1.0f);
	player->SetObjectType(ObjectType::dynamic_);
	//player->SetMeshAsCube(primitive_builder_);
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

void SceneApp::InitScene()
{
//	//Floor
//	floor = GameObject::Create(platform_, world, false);
//
//	floor->SetPosition(0.0f, -2.0f, 0.0f);
//	floor->SetScale(10.0f, 1.0f, 1.0f);
//	floor->SetMeshAsCube(primitive_builder_);
//	floor->AttachPhysicsComponent(world);
//
//	floor->InitialisePhysicsFixture(PhysicsComponent::Shape::BOX,
//		0.0f, //Density
//		1.0f, //Friction
//		0.5,  //Mass
//		false //Is trigger
//	);

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

void SceneApp::InitInput()
{
	//input 
	input = PawnController::Create(platform_);
	input->InitialiseInputManagers(platform_);
	input->PosessPawn(player);
}
                                    