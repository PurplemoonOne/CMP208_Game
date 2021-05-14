#pragma once
#include "State.h"


/*..Pawn Include..*/
#include "Gameobjects/Player.h"
#include "Gameobjects/Planet.h"
#include "Vendor/motion_clip_player.h"
#include "Goal.h"
/*..Camera..*/
#include "Camera/Camera.h"
#include "Camera/ThirdPersonCamera.h"

/*..Physics..*/
#include "Physics/PhysicsComponent.h"
#include "Physics/ContactListener.h"

/*..Input..*/
#include "Input/PawnController.h"

/*..user Interface..*/
#include "UserInterface/UserInterface.h"
#include "UserInterface/UIButton.h"

#include "Utilities/AssetLoader.h"

/*..Skybox..*/
#include "Skybox.h"

/*..Collectables..*/
#include "Collectable.h"


class AudioEmitter;
class GraphicsData;
class ParallaxBackground;
class LevelGenerator;


class GameState : public  State
{
public:
		
	GameState(gef::Platform* platform_, GraphicsData* asset_loader);
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
	gef::Renderer3D* renderer;

	float fps_;
	float timer;
	gef::Font* font;
	gef::Font* health;
	gef::Font* time;

	/*..Initialisers..*/
	void InitFont();
	void SetupLights();
	void InitialiseScene();
	void InitSkybox();
	void InitCamera();
	void InitPlayer(gef::Platform* platform);
	void ResetScene();
	void Tiling();
	//Render functions
	void DrawHUD();
	void RenderSkysphere(gef::Renderer3D* renderer);

	void UpdatePlayer(float delta_time);

	PrimitiveBuilder* primitive_builder_;


	/*..Scene Game objects..*/
	Player* player;
	ContactListener scene_contact_listener;
	UserInterface* user_interface;
	Skybox* skybox;

	/*..Camera..*/
	ThirdPersonCamera* t_camera;

	/*..Box 2D world..*/
	b2World* world;

	/*..Level generator..*/
	LevelGenerator* level;
};

