#include "pch.h"
#include "KeyboardHandler.h"
#include "Event.h"

//Includes
#include "input/input_manager.h"
#include "input/keyboard.h"

KeyboardHandler::KeyboardHandler(gef::InputManager* input_, Pawn* pawn_)
	:input_manager(input_),
	pawn(pawn_),
	w(nullptr),
	a(nullptr),
	s(nullptr),
	d(nullptr),
	up(nullptr),
	down(nullptr),
	left(nullptr),
	right(nullptr),
	shift(nullptr),
	l_alt(nullptr),
	ctrl(nullptr)
{

}

KeyboardHandler::~KeyboardHandler()
{
}

Event* KeyboardHandler::KeyEvents()
{
	gef::Keyboard* keyboard_ = input_manager->keyboard();

	if (keyboard_)
	{

		if (keyboard_->IsKeyDown(gef::Keyboard::KeyCode::KC_W))
		{
			return NULL;// w->action;
		}
		else
		{
			return nullptr;
		}
		/*	else if (keyboard_->IsKeyDown(gef::Keyboard::KC_S))
			{
				return s->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_A))
			{
				return a->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_D))
			{
				return d->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_UP))
			{
				return up->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_DOWN))
			{
				return down->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_RIGHT))
			{
				return right->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_LEFT))
			{
				return left->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_LALT))
			{
				return l_alt->action;
			}
			else if (keyboard_->IsKeyDown(gef::Keyboard::KC_LCONTROL))
			{
				return ctrl->action;
			}*/
	}
}

void KeyboardHandler::ProcessKeybaord(float delta_time)
{
	Event* event_ = KeyEvents();

	if (event_)
	{
		event_->Action(pawn, delta_time);
	}

}

KeyboardHandler* KeyboardHandler::Create(gef::InputManager* input_, Pawn* pawn_)
{
	return new KeyboardHandler(input_, pawn_);
}

void KeyboardHandler::BindKeys(Keys* key, Event* action)
{
	key->action = action;
}

