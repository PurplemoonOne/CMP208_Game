#pragma once
#include "Command.h"

class Jump : public Command
{
public:

	Command* Execute(Pawn* pawn) override
	{
		//pawn.addforce();
	}

	~Jump(){}

};

