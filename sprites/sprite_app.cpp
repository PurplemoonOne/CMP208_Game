#include "sprite_app.h"
#include <system/platform.h>


/*..Renderers..*/
#include <graphics/sprite_renderer.h>
#include <graphics/renderer_3d.h>

/*..Graphics/3D GFX..*/
#include <graphics/font.h>
#include "graphics/mesh_instance.h"

#include <maths/math_utils.h>

/*..Camera..*/
#include "Camera.h"

/*..Pawn Controller..*/
#include "PawnController.h"

SpriteApp::SpriteApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	font_(NULL),
	camera_debugger(NULL),
	player_debugger(NULL),
	render_3D(NULL),
	primitive_builder(NULL),
	main_camera(NULL),
	player_controller(NULL)
{	
}

void SpriteApp::Init()
{
	// create a sprite renderer to draw your sprites
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	render_3D = gef::Renderer3D::Create(platform_);



	/*..Declare Variables Here..*/

	SetupLights();

	InitFont();

	//Primitive Builder
	primitive_builder = new PrimitiveBuilder(platform_);

	//New player object.
	player = Pawn::Create(primitive_builder, platform_);
	player->InitialiseStaticMesh(primitive_builder);


	//Player controller. Doesn't point to anything here.
	player_controller = PawnController::Create(platform_);

	player_controller->PosessPawn(player);


	//Camera object.
	main_camera = Camera::Create(&platform_);
	main_camera->InitialisePerspectiveMatrices();


	//sprite attributes
	my_sprite_.set_position(gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f));

	my_sprite_.set_width(10.0f);
	my_sprite_.set_height(10.0f);
}

void SpriteApp::CleanUp()
{
	CleanUpFont();

	// destroy sprite renderer once you've finished using it
	delete sprite_renderer_;
	sprite_renderer_ = nullptr;

}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;

	HandleInput();

	player->Update(frame_time);

	//Update the camera look at position.
	main_camera->UpdateCameraLookAt(player_controller->MouseLDownPositionCoordinates(), frame_time, player_controller->CanUpdateCamera());

	return true;
}

void SpriteApp::Render()
{
	main_camera->CameraMatrices(render_3D);

	render_3D->Begin();


		player->Render(render_3D);

	render_3D->End();




	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin(false);

	// draw my sprite here
	sprite_renderer_->DrawSprite(my_sprite_);


	DrawHUD();
	sprite_renderer_->End();
}


void SpriteApp::HandleInput()
{
	//Need to set up a way of checking what device is currently being
	//used.
//	player_controller->ProcessSonyController();

	//player_controller->ProcessKeybaord();
	player_controller->ProcessTouchInput();
}

void SpriteApp::InitFont()
{
	// create a Font object and load in the comic_sans font data
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");

	player_debugger = new gef::Font(platform_);
	player_debugger->Load("comic_sans");

	camera_debugger = new gef::Font(platform_);
	camera_debugger->Load("comic_sans");
}

void SpriteApp::CleanUpFont()
{
	// destroy the Font object
	delete font_;
	font_ = NULL;

	delete camera_debugger;
	camera_debugger = nullptr;

	delete player_debugger;
	player_debugger = nullptr;
}

void SpriteApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = render_3D->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}


void SpriteApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(760.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS : %.1f",							// string of text to render
			fps_									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			);
	}


	if (camera_debugger)
	{
		// display frame rate
		camera_debugger->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(2.0f, 48.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"Camera - X: %.1f, Y: %.1f, Z: %.1f",							// string of text to render
			main_camera->GetTranslation().x(),									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			main_camera->GetTranslation().y(),									
			main_camera->GetTranslation().z()								
		);
	}


	if (player_debugger)
	{
		// display frame rate
		player_debugger ->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(2.0f, 24.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"Pawn - X: %.1f, Y: %.1f, Z: %.1f",							// string of text to render
			player->GetPosition().x(),
			player->GetPosition().y(),
			player->GetPosition().z()
		);
	}

}

