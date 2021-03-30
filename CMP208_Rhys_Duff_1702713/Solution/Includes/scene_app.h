#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include "States/GameState.h"
#include "States/MainMenu.h"
#include "States/PauseMenu.h"
#include "States/SplashScreen.h"
#include "States/DeathScreen.h"

#include "Physics/ContactListener.h"

#include "Input/PawnController.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
	class Scene;
}

class Context;

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();

private:

	float fps_;

	Context* context;
	
	//Context* context2;

};

#endif // _SCENE_APP_H
