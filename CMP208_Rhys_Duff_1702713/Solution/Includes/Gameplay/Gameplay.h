#pragma once
/*..Actions..*/
#include "Gameplay/Move.h"
#include "Gameplay/Jump.h"
#include "Gameplay/AddForceToLeftEngine.h"
#include "Gameplay/AddForceToRightEngine.h"


struct Events
{
	MoveLeft move_left;
	MoveRight move_right;
	Jump jump;
	AddForceToLeftEngine force_left_engine;
	AddForceToRightEngine force_right_engine;
};