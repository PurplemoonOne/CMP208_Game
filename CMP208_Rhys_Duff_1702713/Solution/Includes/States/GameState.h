#pragma once
#include "State.h"


/*..Pawn Include..*/
#include "Gameobjects/SpaceShip.h"
#include "Gameobjects/Player.h"
#include "Gameobjects/Planet.h"
/*..Camera..*/
#include "Camera/Camera.h"
#include "Camera/ThirdPersonCamera.h"

#include "Physics/ContactListener.h"
#include "Input/PawnController.h"

#include "UserInterface/UIButton.h"

#include "Utilities/AssetLoader.h"

class GameState : public  State
{
public:

	GameState(gef::Platform* platform_);
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

	void InitFont();
	void CleanUpFont();
	void DrawHUD(gef::SpriteRenderer* sprite_renderer);
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

	void InitInput();

	float fps_;


	/*..Box 2D world..*/
	b2World* world;

	float yPos = 0.0f;

	gef::Mesh* ship_model;
	void LoadSceneModels();
	void CleanModels();
};

