#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include "GameState.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "SplashScreen.h"
#include "DeathScreen.h"

#include "ContactListener.h"



//Debug Physics
#include "b2DebugDraw.h"

#include "PawnController.h"

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
