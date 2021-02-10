#pragma once
#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>

namespace gef
{
	class SonyController;
	class InputManager;
	class TouchInputManager;
	class Platform;
	class Font;

}


class PawnController
{
public:

	PawnController();
	~PawnController();

	void ProcessInputDevices();

protected:



private:

	void InitialiseInputManagers(gef::Platform& platform);

	/*..Input pointers..*/

	gef::SonyController* sce_controller;
	gef::InputManager* input_manager;

	/*.............*/

	/*..Touch Input Attributes..*/

	Int32 active_touch_id_;
	gef::Vector2 touch_position_;

	/*.............*/

};