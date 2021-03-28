#pragma once

namespace gef
{
	class InputManager;
}

/*..Forward Declarations..*/
class Button;
class Event;
class Pawn;

#include "AddForceToLeftEngine.h"
#include "AddForceToRightEngine.h"

class SCE_InputHandler
{
public:

	static SCE_InputHandler* Create(gef::InputManager* input_manager_);

	/// @brief Processes the command that was entered via one of the input devices.
	void ProcessSonyController(float delta_time);

	/// @brief Function responsible for binding buttons.
	void BindButtons();

	~SCE_InputHandler();

	void PossessPawn(Pawn* pawn_);
	void PossessPawn(AnimatedPawn* pawn_);

private:

	/// @brief Handles controller input, returns an action based on what button was pressed.
	/// @return Command* Returns a command to be executed.
	Event* ControllerHandler();

	SCE_InputHandler(gef::InputManager* input_manager_);

	// Pointer to the input manager.
	gef::InputManager* input_manager;

	// Pointer to a pawn object.
	Pawn* pawn;
	AnimatedPawn* anim_pawn;

	/*..Button objects..*/

	///  Button objects used for executing actions.
	///	 Actions can be mapped to different buttons.

	Button* cross;
	Button* circle;
	Button* triangle;
	Button* sqaure;

	Button* dpad_up;
	Button* dpad_down;
	Button* dpad_right;
	Button* dpad_left;

	Button* left_bumper;
	Button* right_bumper;
	Button* left_trigger;
	Button* right_trigger;

	Button* left_stick_button;
	Button* right_stick_button;

	Button* options;
	Button* start;

	/*..Action Mappings..*/
	AddForceToRightEngine add_force_r;
	AddForceToLeftEngine add_force_l;

};

