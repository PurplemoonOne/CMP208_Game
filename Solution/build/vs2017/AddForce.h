#pragma once

#include "Event.h"
#include "box2d/box2d.h"

class AddForce : public Event
{
public:

	virtual void Action(Pawn* pawn, b2World* world)
	{
	  
	}

	~AddForce() {}

};

