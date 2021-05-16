#pragma once

#include "Gameplay/Gameplay.h"

namespace gef
{
	class InputManager;
}

/*..Forward Declarations..*/
class Keys;
class Event;
class Pawn;

class KeyboardHandler
{
private:

	KeyboardHandler(gef::InputManager* input_, Events& events);

public:

	// @brief Creates a new Keyboard handler for the pawn controller class.
	// @param[in] Pointer to the input manager.
	// @param[in] Pointer to the pawn class.
	static KeyboardHandler* Create(gef::InputManager* input_, Events& events);

	/// @brief Function responsible for binding keys.
	void BindKeys(Keys* key, Event* action);

	~KeyboardHandler();

	/// @brief Handles input from the keyboard 
	Event* GetKeyInput();

private:

	Events* _events;

	/*..Pointer to the input manager..*/
	gef::InputManager* input_manager;

	/*..Pointer to the player..*/
	Pawn* pawn;
	AnimatedPawn* anim_pawn;
	PhysicsComponent* phys_object;

	//Get the maximum number of keycodes.
	static const UInt32 MAX_KEY_CODES = gef::Keyboard::KeyCode::NUM_KEY_CODES;


	void BindKeyActions();


	std::array<Keys, MAX_KEY_CODES> key_events;


};

