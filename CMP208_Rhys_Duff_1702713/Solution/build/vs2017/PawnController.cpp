#include "pch.h"
#include "PawnController.h"

/*..gef input devices includes..*/
#include "input/keyboard.h"
#include "input/sony_controller_input_manager.h"

/*..Include command..*/
#include "Event.h"

/*..Camera..*/
#include "Camera.h"

//@brief Variable tracks how many pawn controllers are active. \n For this module there should only be ONE active.
static uint16_t controller_counter = 0;

PawnController::PawnController(gef::Platform& p_ptr)
	:
	platform_ptr(&p_ptr),
	input_manager(NULL),
	active_touch_id_(-1),
	touch_position_(gef::Vector2::kZero)
{

}


PawnController::~PawnController()
{
	if (input_manager)
	{
		delete input_manager;
		input_manager = nullptr;
	}
}

void PawnController::SetPointerToInputManagers(gef::InputManager* input_)
{
	/*..Create a new input manager..*/
	input_manager = input_;

	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager && input_manager->touch_manager() && (input_manager->touch_manager()->max_num_panels() > 0))
		input_manager->touch_manager()->EnablePanel(0);

	keyboard = KeyboardHandler::Create(input_manager, ptr_to_pawn);
	controller = SCE_InputHandler::Create(input_manager, ptr_to_pawn);
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

void PawnController::ProcessInput(float delta_time)
{
	input_manager->Update();
	ProcessTouchInput();
	keyboard->ProcessKeybaord(delta_time);
	controller->ProcessSonyController(delta_time);
}

Event* PawnController::PickAction()
{
	input_manager->Update();
	gef::Keyboard* temp_keyboard = input_manager->keyboard();

	Jump jump;;
	MoveRight move_right;
	AddForceToRightEngine add_force;

	if (temp_keyboard->IsKeyPressed(gef::Keyboard::KeyCode::KC_0))
	{
		return &jump;
	}
	else if (temp_keyboard->IsKeyPressed(gef::Keyboard::KeyCode::KC_1))
	{
		return &move_right;
	}
	else if (temp_keyboard->IsKeyPressed(gef::Keyboard::KeyCode::KC_2))
	{
		return &add_force;
	}

	return nullptr;
}


void PawnController::ControlCamera(Camera* scene_camera, float delta_time)
{
	gef::Keyboard* keyboard_ = input_manager->keyboard();


	if (keyboard_)
	{
			
			if (keyboard_->IsKeyDown(gef::Keyboard::KeyCode::KC_W))
			{
			
				scene_camera->MoveForward(delta_time);
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KeyCode::KC_S))
			{
				scene_camera->MoveBackward(delta_time);
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KeyCode::KC_D))
			{
				scene_camera->MoveRight(delta_time);
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KeyCode::KC_A))
			{
				scene_camera->MoveLeft(delta_time);
			}

		
	}
}

void PawnController::ProcessTouchInput()
{

	const gef::TouchInputManager* touch_input = input_manager->touch_manager();

	/*..This frames mouse information..*/


	if (touch_input && (touch_input->max_num_panels() > 0))
	{
		// get the active touches for this panel
		const gef::TouchContainer& panel_touches = touch_input->touches(0);

		touch_input->panel_enabled(0);

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
					

					frame_mouse_data.mouse_coordinates = &touch_position_;
					frame_mouse_data.mouse_left_button_state = gef::TT_NEW;
				}
			}
			else if (active_touch_id_ == touch->id)
			{
				// we are processing touch data with a matching id to the one we are looking for
				if (touch->type == gef::TT_ACTIVE)
				{
					// update an active touch here
					// we're just going to record the position of the touch


					frame_mouse_data.mouse_coordinates = &touch_position_;
					frame_mouse_data.mouse_left_button_state = gef::TT_ACTIVE;

				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					active_touch_id_ = -1;


					frame_mouse_data.mouse_coordinates = &touch_position_;
					frame_mouse_data.mouse_left_button_state = gef::TT_RELEASED;
				}
			}
		}
	}
}

