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
	class Font;
}

/*..Rhys Duff - 1702713*/
//..Personal Forward Declarations..//
class Pawn;


class PawnController final
{
public:

	PawnController(gef::Platform* p_ptr, Pawn* pawn);
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

	void ControllerHandler();

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

	/*..Pointer to the current posessed pawn object..*/
	Pawn* pawn;

	/*..Pointer to the platform..*/
	gef::Platform* platform_ptr;

};