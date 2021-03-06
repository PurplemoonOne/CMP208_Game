#pragma once
#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>

//Some 'getter' methods require access to variables.
#include "input/touch_input_manager.h"
#include "input/input_manager.h"
#include "KeyboardHandler.h"
#include "SCEInputHandler.h"

/*..Actions..*/
#include "Move.h"
#include "Jump.h"
#include "AddForce.h"


namespace gef
{
	class InputManager;
	class TouchInputManager;
	class Platform;
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
class MoveRight;
class Jump;
class AddForceToRightEngine;
class DButton;

/*..Forward declaration, used as an argument in functions below..*/
class Pawn;
class Camera;

class PawnController final
{
protected:

	/// @brief Pawn controller constructor.
	PawnController(gef::Platform& p_pt);

public:


	// @brief Checks connected input devices to evaluate what has been changed.
	void ProcessInput(float delta_time);


	/// @brief Pawn controller destructor.
	~PawnController();

	/// @brief Gets the scene input manager.
	/// @return Pointer to the input manager.
	gef::InputManager* GetSceneInputManager() { return input_manager; }

	/// @brief Public method used to allocate a pawn controller on the heap.
	/// @param[in] Takes a reference to the application's platform.
	static PawnController* Create(gef::Platform& platform);

	/// @brief Pass a pawn to gain control of that pawn.
	/// @param[in] Takes a pointer to a pawn in the scene.
	void PosessPawn(Pawn* pawn);

	/// @brief Getter to the touch/mouse manager
	inline gef::InputManager* GetTouchInputManager() { return input_manager; }

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

	/// @brief Initialise all input managers supported by the application.
	/// @param[in] A reference to applications current platform.
	void InitialiseInputManagers(gef::Platform& platform);



private:


	/*..TouchInput..*/

	/// @brief Tracks and evaluates touch input.
	void ProcessTouchInput();

	/*..Pick bindings method..*/
	Event* PickAction();

	KeyboardHandler* keyboard;
	SCE_InputHandler* controller;

	/*..Touch input methods..*/

	/// @brief Touch input manager responsible for tracking screen presses, releases and touch updates.
	gef::TouchInputManager* touch_in_manager;

	/*..Touch Input Attributes..*/

	Int32 active_touch_id_;
	gef::Vector2 touch_position_;

	/*..Input pointers..*/

	/// @brief Input manager responsible for handling input queries.
	gef::InputManager* input_manager;

	/*..Pointer to the platform..*/
	gef::Platform* platform_ptr;

	/// @brief Pointer to the current player in the scene.
	Pawn* ptr_to_pawn;

	/// @brief Tracks whether we can grab the mouse coordinates checking if we are pressing left mouse button.
	bool can_get_mouse_coords = false;
};