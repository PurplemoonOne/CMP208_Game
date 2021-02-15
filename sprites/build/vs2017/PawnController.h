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
*	Pawn controller is responsible for handling the input of several devices 
*	as well as allowing the user to posses objects within the game world.
*	Input code is written here allowing greater flexibility when deciding what
*	objects need input.
*/

class PawnController final
{
public:

	PawnController(gef::Platform* p_pt);
	~PawnController();

public:

	void ProcessInputDevices();

	/*..Input pointers..*/
	gef::InputManager* input_manager;

public:

	/*..Keyboard input methods..*/
	gef::Keyboard* keyboard;

public:

	/*..SCE controller manager..*/
	gef::SonyControllerInputManager* sce_in_manager;

	bool ControllerHandler();

public: 

	/*..Touch input methods..*/
	gef::TouchInputManager* touch_in_manager; 

private:

	void InitialiseInputManagers(gef::Platform& platform);


	/*.............*/

	/*..Touch Input Attributes..*/

	Int32 active_touch_id_;
	gef::Vector2 touch_position_;

	/*.............*/

private:

	/*..Pointer to the platform..*/
	gef::Platform* platform_ptr;

};