#include "pch.h"
#include "PawnController.h"

/*..gef input devices includes..*/
#include "input/keyboard.h"
#include "input/sony_controller_input_manager.h"

/*..Include command..*/
#include "Gameplay/Event.h"

#include "system/platform.h"

PawnController::PawnController(gef::Platform& p_ptr, gef::InputManager* input_)
	:
	platform(&p_ptr),
	input_manager(NULL),
	active_touch_id_(-1),
	touch_position_(gef::Vector2::kZero),
	touch_in_manager(nullptr),
	using_controller(false)
{
	/*..Init data..*/

	mouse_data.left_button_state = MouseState::NULL_;

	/*..Create a new input manager..*/
	input_manager = input_;

	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager && input_manager->touch_manager() && (input_manager->touch_manager()->max_num_panels() > 0))
		input_manager->touch_manager()->EnablePanel(0);

	keyboard = KeyboardHandler::Create(input_manager, actions);
	controller = SCE_InputHandler::Create(input_manager, actions);
}

PawnController::~PawnController()
{
	if (input_manager)
	{
		delete input_manager;
		input_manager = nullptr;
	}
}

PawnController* PawnController::Create(gef::Platform& platform, gef::InputManager* input_)
{
	return new PawnController(platform, input_);
}

void PawnController::PosessPawn(Pawn* pawn_)
{
	//First stop pointing to current posessed pawn.
	anim_pawn = nullptr;
	pawn = nullptr;
	phys_object = nullptr;
	//Change pointer to point to new pawn.
	pawn = pawn_;
}

void PawnController::PosessPawn(AnimatedPawn* pawn_)
{
	pawn = nullptr;
	anim_pawn = nullptr;
	phys_object = nullptr;
	anim_pawn = pawn_;
}

void PawnController::PossessPhysObject(PhysicsComponent* phys)
{
	pawn = nullptr;
	anim_pawn = nullptr;
	phys_object = nullptr;

	phys_object = phys;
}

void PawnController::ProcessInput(float delta_time)
{
	//Process the input - Read input from devices 
	//Proceed to execute the event on a valid object.
	input_manager->Update();

	//Read from the controller and keyboard.
	Event* sce_event = controller->GetButtonCode();
	Event* key_event = keyboard->GetKeyInput();

	if (sce_event)
	{
		using_controller = true;
		ExecuteEvent(sce_event, delta_time);
	}
	else if (key_event)
	{
		using_controller = false;
		ExecuteEvent(key_event, delta_time);
	}
	else
	{
		using_controller = false;
	}

	ProcessTouchInput();
}

void PawnController::ExecuteEvent(Event* event_, float delta_time)
{
	/*..Process the command..*/
	//Evaluate which object to peform the command on.
	if (pawn)
	{
		event_->Action(pawn, delta_time);
	}
	else if (anim_pawn)
	{
		event_->Action(anim_pawn, delta_time);
	}
	else if (phys_object)
	{
		event_->Action(phys_object, delta_time);
	}
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


void PawnController::ProcessTouchInput()
{

	const gef::TouchInputManager* touch_input = input_manager->touch_manager();

	/*..This frames mouse information..*/
	mouse_data.coordinates = touch_input->mouse_position();

	// @note Compare mouse coordinates to last frame.
	// If they are the same we must be using the controller.
	// Otherwise we are probably moving the mouse around.
	if ((int)mouse_data.coordinates.x != (int)mouse_data.prev_coordinates.x)
	{
		SetControllerActive(false);
	}
	else //if((int)mouse_data.coordinates.x == (int)mouse_data.prev_coordinates.x)
	{
		SetControllerActive(true);
	}

	mouse_data.prev_coordinates = mouse_data.coordinates;
	mouse_data.left_button_state = MouseState::NULL_;

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
					
					mouse_data.coordinates = touch_position_;
					mouse_data.left_button_state = MouseState::CLICKED;
					using_controller = false;
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

					mouse_data.coordinates = touch_position_;
					mouse_data.left_button_state = MouseState::IS_DOWN;
					using_controller = false;
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					active_touch_id_ = -1;


					mouse_data.coordinates = touch_position_;
					mouse_data.left_button_state = MouseState::RELEASED;
					using_controller = false;
				}
			}
		}
	}
}

