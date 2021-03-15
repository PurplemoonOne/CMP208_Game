#include "pch.h"
#include "SCEInputHandler.h"
#include "Event.h"

/*..gef input includes..*/
#include "input/sony_controller_input_manager.h"
#include "input/input_manager.h"

/*..Actions..*/
#include "AddForceToRightEngine.h"


SCE_InputHandler::SCE_InputHandler(gef::InputManager* input_manager_, Pawn* pawn_)
	:input_manager(input_manager_),
	pawn(pawn_)
{
}

SCE_InputHandler::~SCE_InputHandler()
{

}

void SCE_InputHandler::BindButtons()
{
	/*..Create new button objects..*/
	cross = new Button();

	/*..Create new action objects..*/
	AddForceToRightEngine add_force;

	/*..Asign the actions to the buttons..*/
	cross->action = &add_force;
}


Event* SCE_InputHandler::ControllerHandler()
{

	/*..Point to the sony entertainment controller manager..*/
	/// @brief A pointer to the system's sony controller manager.
	gef::SonyControllerInputManager* sce_in_manager = input_manager->controller_input();

	if (sce_in_manager)
	{

		const gef::SonyController* sce_controller = sce_in_manager->GetController(0);

		if (sce_controller->buttons_down() & gef_SONY_CTRL_CROSS)
		{
			return cross->action;
		}
		else
		{
			return nullptr;
		}
	}

}


SCE_InputHandler* SCE_InputHandler::Create(gef::InputManager* input_manager_, Pawn* pawn_)
{
	return new SCE_InputHandler(input_manager_, pawn_);
}

void SCE_InputHandler::ProcessSonyController(float delta_time)
{
	input_manager->Update();

	Event* event_ = ControllerHandler();

	if (event_ != nullptr)
	{
		event_->Action(pawn, delta_time);
	}
}
