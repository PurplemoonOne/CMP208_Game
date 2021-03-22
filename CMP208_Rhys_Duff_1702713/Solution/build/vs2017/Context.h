#pragma once

#include "State.h"
#include "GameState.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "DeathScreen.h"
#include "PauseMenu.h"

// @brief Tracks the number of contexts running, MAX = 1.
static UInt32 context_count = 0;

class Context
{
public:

	Context(gef::Platform& platform_);
	~Context();


	// @brief Transitions to a new state specified by a string.
	// @param[in] Takes a string to an existing state.
	void Transition(std::string name);
	

	//@brief return the application's current state.
	inline State* CurrentState() const { return state; }

private:

	/*..Store our state instances in a map object..*/
	std::map<std::string, State*> map;

	/*..Pointer to our current state..*/
	State* state;

	/*..Application Variables..*/
	gef::Renderer3D* renderer;
	gef::SpriteRenderer* sprite_renderer;
	gef::Platform* platform;
	gef::PNGLoader* png_loader;
	gef::InputManager* input_manager;

	PawnController* pawn_controller;
};