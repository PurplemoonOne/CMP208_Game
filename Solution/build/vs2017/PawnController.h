#pragma once
#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>

//Some 'getter' methods require access to variables.
#include "input/touch_input_manager.h"
#include "input/input_manager.h"

/*..Actions..*/
#include "Move.h"
#include "Jump.h"
#include "AddForce.h"
#include "DebugButton.h"

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

/*..Actions..*/
class Move;
class Jump;
class AddForce;
class DButton;


/*..Forward Declarations..*/
class Button;
class Keys;
class Event;

/*..Forward declaration, used as an argument in functions below..*/
class Pawn;
class Camera;

class PawnController final
{
protected:

	/// @brief Pawn controller constructor.
	PawnController(gef::Platform& p_pt);

public:

	/// @brief Pawn controller destructor.
	~PawnController();

	/// @brief Gets the scene input manager.
	/// @return Pointer to the input manager.
	//gef::InputManager* GetSceneInputManager() { return input_manager; }

	/// @brief Public method used to allocate a pawn controller on the heap.
	/// @param[in] Takes a reference to the application's platform.
	static PawnController* Create(gef::Platform& platform);

	/// @brief Pass a pawn to gain control of that pawn.
	/// @param[in] Takes a pointer to a pawn in the scene.
	void PosessPawn(Pawn* pawn);

	/// @brief Function responsible for binding buttons.
	void BindButtons();

	/// @brief Function responsible for binding keys.
	void BindKeys();

public:

	/// @brief Getter to the touch/mouse manager
	inline gef::InputManager* GetTouchInputManager() { return input_manager; }

	/// @brief Tracks and evaluates touch input.
	void ProcessTouchInput();

	/*..Keyboard input methods..*/

	/// @brief Evaluate the keys pressed and execute an action.
	void ProcessKeybaord();

	bool iskeydown = false;

public:

	/*..Fly Camera - Debug Mode..*/

	/// @brief Grabs the mouse coordinates when left mouse button is down.
	/// @returns A reference to the mouse coordinates contained in a vector 2.
	inline const gef::Vector2& MouseLDownPositionCoordinates() { return touch_position_; }

	/// @brief Checks if we can update the camera.
	inline bool& CanUpdateCamera() { return can_get_mouse_coords; }

	/// @brief Handles input for the scene camera.
	/// @param[in] Takes a pointer to the scene's camera. 
	/// @param[in] Delta time since the last frame.
	void ControlCamera(Camera* scene_camera, float delta_time);

protected:

	/// @brief Keyboard pointer for key presses and key releases.
	gef::Keyboard* keyboard;

	/// @brief Handles input from the keyboard 
	Event* KeyboardHandler();

public:

	/*..SCE controller manager..*/

	/// @brief Processes the command that was entered via one of the input devices.
	void ProcessSonyController();

protected:

	/// @brief A pointer to the system's sony controller manager.
	gef::SonyControllerInputManager* sce_in_manager;

	/// @brief Handles controller input, returns an action based on what button was pressed.
	/// @return Command* Returns a command to be executed.
	Event* ControllerHandler();


private:


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

	/*..Input pointers..*/

	/// @brief Input manager responsible for handling input queries.
	gef::InputManager* input_manager;

	/*..Pointer to the platform..*/
	gef::Platform* platform_ptr;

	/// @brief Pointer to the current player in the scene.
	Pawn* ptr_to_pawn;

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

	/*..Some more key objects..*/

	Keys* shift;
	Keys* l_alt;
	Keys* ctrl;

private:
	
	/// @brief Tracks whether we can grab the mouse coordinates checking if we are pressing left mouse button.
	bool can_get_mouse_coords = false;



};