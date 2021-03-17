#pragma once
#include "State.h"

class Context
{
private:
	State* state;

public:

	Context(State* state_)
		:
		state(nullptr)
	{
		this->TransitionTo(state_);
	}

	void TransitionTo(State* state_)
	{
		if (this->state != nullptr)
		{
			delete this->state;
			this->state = state_;
			this->state->SetContext(this);
		}
	}
};