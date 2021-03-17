#include "pch.h"

#include "scene_app.h"


//Import from the thread and mutex libraries.
using std::thread;
using std::mutex;
using std::unique_lock;


//Other headers
#include "PawnController.h"


SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	platform(&platform)
{
	renderer = gef::Renderer3D::Create(platform);

	sprite_renderer = gef::SpriteRenderer::Create(platform);

	game = new GameState(platform, *renderer, *sprite_renderer);

}

void SceneApp::Init()
{
	//Splash Screen Here.



}

void SceneApp::CleanUp()
{

}


bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;


	game->Input(frame_time);

	game->Update(frame_time);
	

	return true;
}

void SceneApp::Render()
{
	game->Render();
}

                             