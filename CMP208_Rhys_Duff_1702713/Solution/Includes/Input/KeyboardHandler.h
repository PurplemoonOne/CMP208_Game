#pragma once

#include "Gameplay/Move.h"

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
public:

	// @brief Creates a new Keyboard handler for the pawn controller class.
	// @param[in] Pointer to the input manager.
	// @param[in] Pointer to the pawn class.
	static KeyboardHandler* Create(gef::InputManager* input_);

	/// @brief Function responsible for binding keys.
	void BindKeys(Keys* key, Event* action);

	/// @brief Evaluate the keys pressed and execute an action.
	void ProcessKeybaord(float delta_time);

	~KeyboardHandler();

	// @brief Take control of a pawn.
	// @param[in] Pointer to a pawn.
	void PossessPawn(Pawn* pawn_); 

	// @brief Take control of an animated pawn.
	// @param[in] Pointer to a animated pawn.
	void PossessPawn(AnimatedPawn* pawn_);

private:



	/// @brief Handles input from the keyboard 
	Event* KeyEvents();

	KeyboardHandler(gef::InputManager* input_);

	/*..Pointer to the input manager..*/
	gef::InputManager* input_manager;

	/*..Pointer to the player..*/
	Pawn* pawn;
	AnimatedPawn* anim_pawn;

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

	MoveLeft move_left;
	MoveRight move_right;

};

