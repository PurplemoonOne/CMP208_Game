#include "pch.h"
#include "SCEInputHandler.h"
#include "Gameplay/Event.h"

/*..gef input includes..*/
#include "input/input_manager.h"
#include "input/sony_controller_input_manager.h"


/*..Actions..*/
#include "Gameplay/AddForceToRightEngine.h"

//@brief Variable tracks how many pawn controllers are active. 
static uint32 controller_counter = 0;

SCE_InputHandler::SCE_InputHandler(gef::InputManager* input_manager_, Events& events)
	:input_manager(input_manager_),
	pawn(nullptr),
	anim_pawn(nullptr)
{

	left_joystick = new Joystick();
	right_joystick = new Joystick();

	InitialiseButtons();
	BindButtons();
}

SCE_InputHandler::~SCE_InputHandler()
{
	delete left_joystick;
	left_joystick = nullptr;

	delete right_joystick;
	right_joystick = nullptr;
}

void SCE_InputHandler::BindButtons()
{
	left_joystick->action[0] = &move_right;
	left_joystick->action[1] = &move_left;
	
	buttons[(int)ControllerCodes::cross].action[(int)DeviceState::released] = &jump;
	buttons[(int)ControllerCodes::cross].action[(int)DeviceState::is_down] = &charge_jump;

	buttons[(int)ControllerCodes::left].action[(int)DeviceState::is_down] = &move_left;
	buttons[(int)ControllerCodes::right].action[(int)DeviceState::is_down] = &move_right;
}

SCE_InputHandler* SCE_InputHandler::Create(gef::InputManager* input_manager_, Events& events)
{
	return new SCE_InputHandler(input_manager_, events);
}


void SCE_InputHandler::InitialiseButtons()
{
	UInt32 codes[] =
	{
		gef_SONY_CTRL_SELECT,	

		gef_SONY_CTRL_L3,		 
		gef_SONY_CTRL_R3,	

		gef_SONY_CTRL_START,	 
		gef_SONY_CTRL_OPTIONS,	

		gef_SONY_CTRL_UP,		 
		gef_SONY_CTRL_RIGHT,	 
		gef_SONY_CTRL_DOWN,		 
		gef_SONY_CTRL_LEFT,

		gef_SONY_CTRL_L2,		 
		gef_SONY_CTRL_R2,	

		gef_SONY_CTRL_L1,		 
		gef_SONY_CTRL_R1,	

		gef_SONY_CTRL_TRIANGLE,	 
		gef_SONY_CTRL_CIRCLE,	 
		gef_SONY_CTRL_CROSS,	 
		gef_SONY_CTRL_SQUARE,

		gef_SONY_CTRL_TOUCH_PAD	 
	};

	for (int index = 0; index < button_codes.size(); ++index)
	{
		button_codes[index] = codes[index];
	}

}

Event* SCE_InputHandler::GetButtonCode()
{

	gef::SonyControllerInputManager* sce_in_manager = input_manager->controller_input();

	Event* event_ = nullptr;

	if (sce_in_manager)
	{
		const gef::SonyController* controller = sce_in_manager->GetController(controller_counter);

			if (controller)
			{
					for (int index = 0; index < button_codes.size(); ++index)
					{
					
				
							if (controller->buttons_pressed() == button_codes[index])
							{
								gef::DebugOut("Pressing Button %i\n", button_codes[index]);
				
								if (buttons[index].action[(UInt32)DeviceState::pressed] != nullptr)
								{
									event_ = buttons[index].action[(UInt32)DeviceState::pressed];

									return event_;
								}
									
							}
							else if (controller->buttons_down() == button_codes[index])
							{
				
								gef::DebugOut("Holding Button %i\n", button_codes[index]);
							
								if (buttons[index].action[(UInt32)DeviceState::is_down] != nullptr)
								{
									event_ = buttons[index].action[(UInt32)DeviceState::is_down];
							
									return event_;
								}
									
							}
							else if (controller->buttons_released() == button_codes[index])
							{
								gef::DebugOut("Releasing Button %i\n", button_codes[index]);
				
								if (buttons[index].action[(UInt32)DeviceState::released] != nullptr)
								{
									event_ = buttons[index].action[(UInt32)DeviceState::released];
				
									return event_;
								}
							}
					}

					//Check Joystick.
					if (controller->left_stick_x_axis() > gef::DegToRad(0.0f))
					{
						return event_ = left_joystick->action[0];
					}
					if (controller->left_stick_x_axis() < gef::DegToRad(0.0f))
					{
						return event_ = left_joystick->action[1];
					}

			}

	}

	return nullptr;
}
