#include "PawnController.h"

/*..gef input devices includes..*/
#include "input/keyboard.h"
#include "input/sony_controller_input_manager.h"

/*..Include command..*/
#include "Command.h"


/*..Actions..*/
#include "Move.h"
#include "Camera.h"

//@brief Variable tracks how many pawn controllers are active. \n For this module there should only be ONE active.
static uint16_t controller_counter = 0;

PawnController::PawnController(gef::Platform& p_ptr)
	:
	platform_ptr(&p_ptr),

	input_manager(nullptr),
	active_touch_id_(-1),
	touch_position_(gef::Vector2::kZero)
{

	InitialiseInputManagers(*platform_ptr);

}


PawnController::~PawnController()
{
	//On application close, delete this from memory.
	//delete this;
}

void PawnController::InitialiseInputManagers(gef::Platform& platform)
{
	/*..Create a new input manager..*/
	input_manager = gef::InputManager::Create(platform);

	/*..Point to the keyboard manager..*/
	keyboard = input_manager->keyboard();

	/*..Point to the sony entertainment controller manager..*/
	sce_in_manager = input_manager->controller_input();

	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager && input_manager->touch_manager() && (input_manager->touch_manager()->max_num_panels() > 0))
		input_manager->touch_manager()->EnablePanel(0);
}


PawnController* PawnController::Create(gef::Platform& platform)
{
	if (controller_counter == 0) 
	{
		controller_counter++;
		return new PawnController(platform);
	}
	else
	{
		/*
		*	There shouldn't more than one controller at a time.
		*	In future however if developing a game supporting coop 
		*	or a game running on a network may support more than one.
		*/
	}
}

void PawnController::PosessPawn(Pawn* pawn)
{
	//First stop pointing to current posessed pawn.
	ptr_to_pawn = nullptr;

	//Change pointer to point to new pawn.
	ptr_to_pawn = pawn;

}

void PawnController::BindButtons()
{

	

}

void PawnController::BindKeys()
{
}

void PawnController::ControlCamera(Camera* scene_camera, float delta_time)
{

	if (keyboard)
	{

			if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_W))
			{
				iskeydown = true;
				scene_camera->MoveForward(delta_time);
			}
			else if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_S))
			{
				scene_camera->MoveBackward(delta_time);
			}
			else if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_D))
			{
				scene_camera->MoveRight(delta_time);
			}
			else if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_A))
			{
				scene_camera->MoveLeft(delta_time);
			}
			else
			{
				iskeydown = false;
			}
	}
}

void PawnController::ProcessTouchInput()
{
	const gef::TouchInputManager* touch_input = input_manager->touch_manager();

	bool validate_input = (touch_input && (touch_input->max_num_panels() > 0));

	if (validate_input)
	{
		// get the active touches for this panel
		const gef::TouchContainer& panel_touches = touch_input->touches(0);

		// go through the touches
		for (gef::ConstTouchIterator touch = panel_touches.begin(); touch != panel_touches.end(); ++touch)
		{
			// if active touch id is -1, then we are not currently processing a touch
			if (active_touch_id_ == -1)
			{
				// check for the start of a new touch
				if (touch->type == gef::TT_NEW)
				{
					active_touch_id_ = touch->id;

					// do any processing for a new touch here
					// we're just going to record the position of the touch
					touch_position_ = touch->position;
				}
			}
			else if (active_touch_id_ == touch->id)
			{
				// we are processing touch data with a matching id to the one we are looking for
				if (touch->type == gef::TT_ACTIVE)
				{
					// update an active touch here
					// we're just going to record the position of the touch
					touch_position_ = touch->position;
					can_get_mouse_coords = true;
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					active_touch_id_ = -1;
					can_get_mouse_coords = false;
				}
			}
		}
	}
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
	Event* event_ = ControllerHandler()->action;

	if (event_)
	{
		event_->Action(ptr_to_pawn);
	}
}

Keys* PawnController::KeyboardHandler()
{

		/*if (keyboard->IsKeyPressed(gef::Keyboard::KC_W))
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
		}*/

	return nullptr;
}

void PawnController::ProcessKeybaord()
{

	Event* event_ = KeyboardHandler()->action;

	if (event_)
	{
		event_->Action(ptr_to_pawn);
	}

}

