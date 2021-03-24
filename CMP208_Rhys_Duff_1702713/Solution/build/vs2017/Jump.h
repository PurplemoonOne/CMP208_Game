#pragma once
#include "Event.h"

class Jump : public Event
{
public:

	void Action(Pawn* pawn, float delta_time) override
	{

	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{
		NULL;
	}

	~Jump(){}

};

