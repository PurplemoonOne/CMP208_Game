#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>

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

	/*..Initialise the 2D body..*/
	b2BodyDef body_definition;//Needs a definition
	body_definition.type = b2_dynamicBody;
	body_definition.position = b2Vec2(0.0f, 0.0f);

	body = world->CreateBody(&body_definition);

	b2PolygonShape box_collider;
	box_collider.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixture_def;
	fixture_def.shape = &box_collider;
	fixture_def.density = 0.2f;
	fixture_def.density = 1.0f;

	b2Fixture* fixture = body->CreateFixture(&fixture_def);

}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	// setup the mesh for the player
	player_.set_mesh(primitive_builder_->GetDefaultCubeMesh());

	InitFont();
	SetupLights();
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

	/*..Clean up 2D physics world..*/
	delete world;
	world = nullptr;
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	const uint32 velocity_iterations = 6;
	const uint32 position_iterations = 2;

	/*
	* Update the physics world, iteration variables dictate the quality of the simulations.
	*/
	world->Step(frame_time, velocity_iterations, position_iterations);

	//Get the physics body's y position.
	yPos = body->GetTransform().p.y;

	gef::Matrix44 player_transform;
	player_transform.SetIdentity();
	player_transform.RotationZ(body->GetTransform().q.GetAngle());
	player_transform.SetTranslation(gef::Vector4(body->GetPosition().x, body->GetPosition().y, 0.0f));


	player_.set_transform(player_transform);
	return true;
}

void SceneApp::Render()
{
	// setup camera

	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(-2.0f, 2.0f, 5.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);


	// draw 3d geometry
	renderer_3d_->Begin();

	renderer_3d_->set_override_material(&primitive_builder_->red_material());
	renderer_3d_->DrawMesh(player_);
	renderer_3d_->set_override_material(NULL);

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
	if(font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_,
			gef::Vector4(600.0f, 510.0f, -0.9f),
			1.0f, 0xffffffff, gef::TJ_LEFT,
			"Y-Position %.1f FPS: %.1f",
			yPos,
			fps_
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
