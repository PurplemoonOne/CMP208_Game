#pragma once
#include "GameState.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "DeathScreen.h"
#include "PauseMenu.h"
#include "Options.h"

#include "Audio.h"
#include "Vendor/audio_3d.h"
#include "GraphicsData.h"

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

	inline gef::SpriteRenderer* SpriteRenderer() const { return sprite_renderer; }

	inline gef::Platform* GetPlatform() const { return platform; }

	inline Audio* GetAudio() const { return audio; }

	inline GraphicsData* GFXData() const { return graphics_data; }

	inline void SetGameIsRunning(bool running) { is_game_running = running; }
	inline const bool& GameRunning() { return is_game_running; }

	inline void Reset(bool running) { reset = running; }
	inline const bool& IsReset() { return reset; }

private:
	/*..Store our state instances in a map object..*/
	std::map<States, State*> map;

	/*..Pointer to our current state..*/
	State* state;
	bool is_game_running;
	bool reset;

	/*..Application Variables..*/
	gef::SpriteRenderer* sprite_renderer;
	gef::Platform* platform;
	gef::InputManager* input_manager;
	
	Audio* audio;
	PawnController* pawn_controller;
	GraphicsData* graphics_data;
};