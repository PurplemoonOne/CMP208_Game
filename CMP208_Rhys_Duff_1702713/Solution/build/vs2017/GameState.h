#pragma once
#include "State.h"


/*..Pawn Include..*/
#include "SpaceShip.h"
#include "Player.h"
#include "Planet.h"
/*..Camera..*/
#include "Camera.h"
#include "ThirdPersonCamera.h"

#include "ContactListener.h"
#include "PawnController.h"

#include "UIButton.h"

#include "AssetLoader.h"

class GameState : public  State
{
public:

	GameState(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* input);
	~GameState();

	// @brief Called when we transition
	// @note Acts as a buffer allowing us to activate/assume any process
	//that was previously on hold. We try NOT instantiate new objects here.
	virtual void OnEnter() override;

	// @brief Handles the input from the user. Allows control of 'pawns'
	virtual void Input(float delta_time) override;

	// @brief Updates the game state.
	virtual bool Update(float delta_time) override;
	 
	// @brief Renders the main game.
	virtual void Render() override;

	// @brief Called when we leave this state.
	// @note Like OnEnter but pauses processes if need be.
	virtual void OnExit() override;

private:

	/*..Application Variables..*/
	gef::Platform* platform;
	gef::Renderer3D* renderer;
	gef::SpriteRenderer* sprite_renderer;

	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();

	gef::Font* font_;

	PrimitiveBuilder* primitive_builder_;

	//My Includes
	void InitPlayer();
	void InitScene();

	std::vector<GameObject*> essential_objects;
	std::vector<AnimatedGameObject*> essential_anim_objects;
	std::vector<GameObject*> dynamic_objects;

	ContactListener scene_contact_listener;

	Camera* camera;
	ThirdPersonCamera* t_camera;

	PawnController* pawn_controller;
	void InitInput();

	float fps_;


	/*..Box 2D world..*/
	b2World* world;

	float yPos = 0.0f;

	//Loading assets.
	AssetLoader* asset_loader;

	gef::Mesh* ship_model;
	void LoadSceneModels();
	void CleanModels();
};

