#pragma once
#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>

namespace gef
{
	class InputManager;
	class SonyController;
	class SonyControllerInputManager;
	class TouchInputManager;
	class Platform;
	class Keyboard;
	class Font;
}

/*
* 
*	Pawn controller is responsible for handling the input of several devices 
*	as well as allowing the user to posses objects within the game world.
* 
* 
*	Input code is written here allowing greater flexibility when deciding what
*	objects need input i.e supports multiple input objects.
* 
*/

class Button;
class Keys;

class Pawn;

class PawnController final
{
public:

	PawnController(gef::Platform* p_pt);
	~PawnController();

public:

	/*..Input pointers..*/

	/// @brief Input manager responsible for handling input queries.
	gef::InputManager* input_manager;

public:

	/*..Keyboard input methods..*/

	/// @brief Evaluate the keys pressed and execute an action.
	void ProcessKeybaord();

	/// @brief Keyboard pointer for key presses and key releases.
	gef::Keyboard* keyboard;

	/// @brief Handles input from the keyboard 
	Keys* KeyboardHandler();

public:


	/*..SCE controller manager..*/

	/// @brief Processes the command that was entered via one of the input devices.
	void ProcessSonyController();

	/// @brief A pointer to the system's sony controller manager.
	gef::SonyControllerInputManager* sce_in_manager;

	/// @brief Handles controller input, returns an action based on what button was pressed.
	/// @return Command* Returns a command to be executed.
	Button* ControllerHandler();


public: 


	/*..Touch input methods..*/

	/// @brief Touch input manager responsible for tracking screen presses, releases and touch updates.
	gef::TouchInputManager* touch_in_manager; 


private:

	/// @brief Initialise all input managers supported by the application.
	/// @param[in] A reference to applications current platform.
	void InitialiseInputManagers(gef::Platform& platform);


	/*.............*/

	/*..Touch Input Attributes..*/

	Int32 active_touch_id_;
	gef::Vector2 touch_position_;

	/*.............*/

private:

	/*..Pointer to the platform..*/


	gef::Platform* platform_ptr;

	/*..Pawn currently posessed..*/

	/// @brief This is a pointer to the currently controlled pawn.
	Pawn* pawn;

private:

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

private:

	/*..Key objects..*/

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

};