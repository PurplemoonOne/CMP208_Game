#pragma once
#include "input/keyboard.h"

class Pawn;


enum EventStatus
{
	E_PRESSED = 0,
	E_ACTIVE,
	E_RELEASED
};


class Event
{
public:
	/*
	* Base command class. Responsible for mapping keys and buttons to 
	* commands.
	*/

	/// @brief Executes the action bound to the key. (or button)
	/// @param[in] Pointer to the pawn in which the action is associated with.
	virtual void Action(Pawn* pawn) = 0;
	virtual ~Event() {}

};

class Keys 
{
public:
	Event* action;
	EventStatus event_status;
};

class Button
{
public:
	Event* action;
	EventStatus event_status;
};
