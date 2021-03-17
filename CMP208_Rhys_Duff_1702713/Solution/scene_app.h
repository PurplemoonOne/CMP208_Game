#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include "GameState.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "SplashScreen.h"


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

class State;

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();

private:

	gef::Renderer3D* renderer;
	gef::SpriteRenderer* sprite_renderer;
	gef::Platform* platform;

	float fps_;

	State* state;
	GameState* game;

};

#endif // _SCENE_APP_H
