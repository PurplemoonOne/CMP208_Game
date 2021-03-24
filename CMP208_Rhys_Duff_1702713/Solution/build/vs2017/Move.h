#pragma once
#include "Event.h"
#include "Pawn.h"

class MoveRight : public Event
{
public:


	void Action(Pawn* pawn, float delta_time)
	{

	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{
	
	}

	~MoveRight(){}
};