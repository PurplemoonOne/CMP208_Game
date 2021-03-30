#pragma once
#include "GameState.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "DeathScreen.h"
#include "PauseMenu.h"
#include "Options.h"

#include "audio/audio_manager.h"

enum class States
{
	SPLASH = 0,
	MAIN,
	GAME,
	PAUSE,
	OPTIONS,
	DEATH,
	NULL_
};

// @brief Tracks the number of contexts running, MAX = 1.
static UInt32 context_count = 0;

class Context
{
public:

	Context(gef::Platform& platform_);
	~Context();


	// @brief Transitions to a new state specified by a string.
	// @param[in] Takes a string to an existing state.
	void Transition(States name);
	

	//@brief return the application's current state.
	inline State* CurrentState() const { return state; }

	// @Grab the input.
	inline PawnController* GetInput() const { return pawn_controller; }

	inline AssetLoader* GetAssetLoader() const { return asset_loader; }

	inline gef::Renderer3D* Renderer() const { return renderer; }

	inline gef::SpriteRenderer* SpriteRenderer() const { return sprite_renderer; }

	inline gef::AudioManager* AudioManager() const { return audio_manager; }

	inline gef::Platform* GetPlatform() const { return platform; }

private:

	/*..Store our state instances in a map object..*/
	std::map<States, State*> map;

	/*..Pointer to our current state..*/
	State* state;

	/*..Application Variables..*/
	gef::Renderer3D* renderer;
	gef::SpriteRenderer* sprite_renderer;
	gef::Platform* platform;
	gef::InputManager* input_manager;
	gef::AudioManager* audio_manager;
	PawnController* pawn_controller;
	AssetLoader* asset_loader;
};