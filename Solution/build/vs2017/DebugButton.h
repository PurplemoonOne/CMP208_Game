#pragma once
#include "Event.h"
#include <system/debug_log.h>

class DButton : public Event
{
public:
	virtual void Action(Pawn* pawn) override
	{
		if (pawn) {
			gef::DebugOut("Button's Action is being called.");
		
		}
		else
		{
			gef::DebugOut("Pawn is NULL.");
	
		}
	}
};

