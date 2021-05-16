#include "pch.h"
#include "pch.h"
#include "KeyboardHandler.h"
#include "Gameplay/Event.h"

//Includes
#include "input/input_manager.h"
#include "input/keyboard.h"

KeyboardHandler::KeyboardHandler(gef::InputManager* input_, Events& events_)
	:
	input_manager(input_),
	_events(&events_),
	pawn(nullptr),
	anim_pawn(nullptr)
{
	BindKeyActions();
}

KeyboardHandler::~KeyboardHandler()
{
}

Event* KeyboardHandler::GetKeyInput()
{

	Event* event_ = nullptr;

	const gef::Keyboard* keyboard = input_manager->keyboard();

	for (int index = 0; index < key_events.size(); ++index)
	{

			if (keyboard->IsKeyPressed((gef::Keyboard::KeyCode)index))
			{

					if (key_events[index].action[(UInt32)DeviceState::pressed] != nullptr)
					{

								event_ = key_events[index].action[(UInt32)DeviceState::pressed];
								return event_;
					}

			}
			else if (keyboard->IsKeyDown((gef::Keyboard::KeyCode)index))
			{

					if (key_events[index].action[(UInt32)DeviceState::is_down] != nullptr)
					{

								event_ = key_events[index].action[(UInt32)DeviceState::is_down];
								return event_;

					}

			}
			else if (keyboard->IsKeyReleased((gef::Keyboard::KeyCode)index))
			{

					if (key_events[index].action[(UInt32)DeviceState::released] != nullptr)
					{

							event_ = key_events[index].action[(UInt32)DeviceState::released];
							return event_;
	
					}

			}

	}

	return nullptr;
}

void KeyboardHandler::BindKeyActions()
{
	//Bind the keys to the respective actions.
	key_events[(int)gef::Keyboard::KeyCode::KC_D].action[(int)DeviceState::is_down] = &_events->move_right;
	key_events[(int)gef::Keyboard::KeyCode::KC_A].action[(int)DeviceState::is_down] = &_events->move_left;

	key_events[(int)gef::Keyboard::KeyCode::KC_SPACE].action[(int)DeviceState::released] = &_events->jump;
	key_events[(int)gef::Keyboard::KeyCode::KC_SPACE].action[(int)DeviceState::is_down] = &_events->charge_jump;
}




KeyboardHandler* KeyboardHandler::Create(gef::InputManager* input_, Events& events)
{
	return new KeyboardHandler(input_, events);
}

void KeyboardHandler::BindKeys(Keys* key, Event* action)
{

}

