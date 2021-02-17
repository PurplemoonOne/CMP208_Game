#include "PawnController.h"

/*..gef input devices includes..*/
#include "input/input_manager.h"
#include "input/keyboard.h"
#include "input/sony_controller_input_manager.h"
#include "input/touch_input_manager.h"

/*..Include command..*/
#include "Command.h"


PawnController::PawnController(gef::Platform* p_ptr)
	:
	platform_ptr(p_ptr),

	input_manager(nullptr),
	active_touch_id_(-1),
	touch_position_(gef::Vector2::kZero)
{

}

PawnController::~PawnController()
{
}

void PawnController::InitialiseInputManagers(gef::Platform& platform)
{
	/*..Create a new input manager..*/
	input_manager = gef::InputManager::Create(platform);

	/*..Create a new sony entertainment controller manager..*/
	sce_in_manager = input_manager->controller_input();


	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager && input_manager->touch_manager() && (input_manager->touch_manager()->max_num_panels() > 0))
		input_manager->touch_manager()->EnablePanel(0);

}

Button* PawnController::ControllerHandler()
{
		const gef::SonyController* sce_controller = sce_in_manager->GetController(0);

		if (sce_controller)
		{
				switch (sce_controller->buttons_pressed())
				{
					case gef_SONY_CTRL_OPTIONS:
	
						return options;

						break;
					case gef_SONY_CTRL_CROSS:

						return cross;

						break;
					case gef_SONY_CTRL_CIRCLE:
						
						return circle;

						break;
					case gef_SONY_CTRL_TRIANGLE:
	
						return triangle;
	
						break;
					case gef_SONY_CTRL_SQUARE:
	
						return sqaure;
	
						break;
					case gef_SONY_CTRL_UP:
	
						return dpad_up;
	
						break;
					case gef_SONY_CTRL_RIGHT:
	
						return dpad_right;

						break;
					case gef_SONY_CTRL_DOWN:
	
						return dpad_down;
	
						break;
					case gef_SONY_CTRL_LEFT:
	
						return dpad_left;

						break;
					case gef_SONY_CTRL_L1:
	
						return left_bumper;
	
						break;
					case gef_SONY_CTRL_L2:
	
						return left_trigger;

						break;
					case gef_SONY_CTRL_L3:
	
						return left_stick_button;

						break;
					case gef_SONY_CTRL_R1:
	
						return right_bumper;
	
						break;
					case gef_SONY_CTRL_R2:
	
						return right_trigger;

						break;
					case gef_SONY_CTRL_R3:
	
						return right_stick_button;
				
						break;	
					case gef_SONY_CTRL_CIRCLE & gef_SONY_CTRL_CROSS:

						//Custom button Needed

						break;
					default:
						
						break;
				}
		}
	

		return nullptr;
}

void PawnController::ProcessSonyController()
{
	Event* event_ = ControllerHandler();

	if (event_)
	{
		event_->Action(nullptr);
	}
}

Keys* PawnController::KeyboardHandler()
{


		if (keyboard->IsKeyPressed(gef::Keyboard::KC_W))
		{

				return w;

		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_S))
		{

				return s;

		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_A))
		{

				return a;

		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_D))
		{

				return d;

		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_UP))
		{

				return up;

		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_DOWN))
		{

				return down;

		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_RIGHT))
		{

				return right;
				
		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_LEFT))
		{

				return left;

		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_LALT))
		{

				return l_alt;
				
		}
		else if (keyboard->IsKeyPressed(gef::Keyboard::KC_LCONTROL))
		{

				return ctrl;

		}


	return nullptr;
}

void PawnController::ProcessKeybaord()
{

	Event* event_ = KeyboardHandler();

	if (event_)
	{
		event_->Action(nullptr);
	}

}

