#pragma once

class Pawn;

class Event
{
public:

	/*
	* Base command class. Responsible for mapping keys and buttons to 
	* commands.
	*/

	virtual ~Event() {}

	/// @brief Executes the action bound to the key. (or button)
	/// @param[in] Pointer to the pawn in which the action is associated with.
	virtual Event* Action(Pawn* pawn) = 0;

};

class Keys : public Event
{
public:
	Keys* key;
};

class Button : public Event
{
public:
	Button* button;
};
