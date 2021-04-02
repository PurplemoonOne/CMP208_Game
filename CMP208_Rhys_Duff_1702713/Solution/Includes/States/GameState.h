#pragma once
#include "State.h"


/*..Pawn Include..*/
#include "Gameobjects/SpaceShip.h"
#include "Gameobjects/Player.h"
#include "Gameobjects/Planet.h"
/*..Camera..*/
#include "Camera/Camera.h"
#include "Camera/ThirdPersonCamera.h"

/*..Physics..*/
#include "Physics/PhysicsComponent.h"

#include "Physics/ContactListener.h"
#include "Input/PawnController.h"

#include "UserInterface/UIButton.h"

#include "Utilities/AssetLoader.h"

class AudioEmitter;

class GameState : public  State
{
public:

	GameState(gef::Platform* platform_, AssetLoader* asset_loader);
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
	float fps_;


	void InitFont();
	void InitInput();
	void InitAudio();
	void CleanUpFont();
	void DrawHUD(gef::SpriteRenderer* sprite_renderer);
	void SetupLights();

	gef::Font* font_;

	PrimitiveBuilder* primitive_builder_;

	//My Includes
	void InitPlayer(AssetLoader* asset_loader, gef::Platform* platform);
	void InitScene(AssetLoader* asset_loader, gef::Platform* platform);


	//Gameobjects
	std::vector<GameObject*> environment_objects;
	std::vector<PhysicsComponent*> physics_components;

	std::vector<GameObject*> dynamic_objects;


	Player* player;
	PhysicsComponent* player_phys;

	ContactListener scene_contact_listener;

	//Camera
	Camera* camera;
	ThirdPersonCamera* t_camera;

	/*..Box 2D world..*/
	b2World* world;

	float yPos = 0.0f;

	gef::Mesh* ship_model;
	void LoadSceneModels(AssetLoader* asset_loader, gef::Platform* platform);
	void CleanModels();
};

