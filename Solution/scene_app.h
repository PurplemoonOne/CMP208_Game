#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include "SceneHandler.h"

//Debug Physics
#include "b2DebugDraw.h"

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

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();

	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);
    
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Renderer3D* renderer_3d_;

	PrimitiveBuilder* primitive_builder_;

	gef::Scene scene_assets_;


	//My Includes
	Pawn* player;
	void InitPlayer();
	GameObject* floor;
	void InitScene();
	Planet* planet;

	Camera* camera;
	PawnController* input;
	void InitInput();

	float fps_;

	/*..Box 2D world..*/
	b2World* world;

	float yPos = 0.0f;
};

#endif // _SCENE_APP_H
