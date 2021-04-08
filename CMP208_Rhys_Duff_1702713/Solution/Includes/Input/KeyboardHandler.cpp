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
	events(&events_),
	pawn(nullptr),
	anim_pawn(nullptr),
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
	ctrl(nullptr),
	space_bar(nullptr)
{
	a = new Keys();
	d = new Keys();
	space_bar = new Keys();

	a->action = &events->move_left;
	d->action = &events->move_right;
	space_bar->action = &events->jump;
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
			if(w)
			return w->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_S))
		{
			if(s)
			return s->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_A))
		{
			if(a)
			return a->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_D))
		{
			if(d)
			return d->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_UP))
		{
			if(up)
			return up->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_DOWN))
		{
			if(down)
			return down->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_RIGHT))
		{
			if(right)
			return right->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_LEFT))
		{
			if(left)
			return left->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_LALT))
		{
			if(l_alt)
			return l_alt->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KC_LCONTROL))
		{
			if(ctrl)
			return ctrl->action;
		}
		else if (keyboard_->IsKeyDown(gef::Keyboard::KeyCode::KC_SPACE))
		{
			if (space_bar)
				return space_bar->action;
		}
		
		return nullptr;
	}
}

KeyboardHandler* KeyboardHandler::Create(gef::InputManager* input_, Events& events)
{
	return new KeyboardHandler(input_, events);
}

void KeyboardHandler::BindKeys(Keys* key, Event* action)
{
	key->action = action;
}

