#pragma once
#include "Event.h"

class Jump : public Event
{
public:

	virtual void Action(Pawn* pawn) override
	{
		//Jump.
	}

	~Jump(){}

};

