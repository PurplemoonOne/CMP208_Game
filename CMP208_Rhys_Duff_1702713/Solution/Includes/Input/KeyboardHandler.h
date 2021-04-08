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
	Event* KeyEvents();

private:

	Events* events;

	/*..Pointer to the input manager..*/
	gef::InputManager* input_manager;

	/*..Pointer to the player..*/
	Pawn* pawn;
	AnimatedPawn* anim_pawn;
	PhysicsComponent* phys_object;

	/*..w,a,s,d..*/

	Keys* w;
	Keys* a;
	Keys* s;
	Keys* d;

	/*..up key, down key, left key and right key..*/

	Keys* up;
	Keys* down;
	Keys* left;
	Keys* right;

	/*..Some more key objects..*/

	Keys* shift;
	Keys* l_alt;
	Keys* ctrl;
	Keys* space_bar;

};

