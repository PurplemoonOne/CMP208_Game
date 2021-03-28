#include "pch.h"
#include "AnimDriver.h"

AnimDriver::AnimDriver()
{
	state = nullptr;
}

AnimDriver::~AnimDriver()
{
}

void AnimDriver::Transition(AnimId name)
{
	if (state != nullptr) {
		this->state->OnExit();//Clear any data in the current state.
	}


	this->state = map.at(name);

	this->state->OnTransition();

	this->state->SetDriver(this);
}

void AnimDriver::InsertAnimation(AnimId name, AnimState* state)
{
	map[name] = state;
}
