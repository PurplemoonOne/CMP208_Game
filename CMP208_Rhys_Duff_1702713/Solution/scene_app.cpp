#include "pch.h"

#include "scene_app.h"
#include "Context.h"

//Import from the thread and mutex libraries.
using std::thread;
using std::mutex;
using std::unique_lock;


//Other headers
#include "PawnController.h"




SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	fps_(0.0f),
	context(nullptr)
{
	/*..Create our new application context..*/
	context = new Context(platform);
	
	/*..This just demonstrates you cannot have more than one game context running at a time.*/
	//context2 = new State(platform);
}

void SceneApp::Init()
{
	//Splash Screen Here.
	context->Transition("Splash");

}

void SceneApp::CleanUp()
{
	delete context;
	context = nullptr;
}


bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	// @note 'Context' : Drives the current state
	// hence 
	context->CurrentState()->Input(frame_time);
	
	return context->CurrentState()->Update(frame_time);
}

void SceneApp::Render()
{
	context->CurrentState()->Render();
}

                             