#pragma once

class Pawn;

class Command
{
public:

	/*
	* Base command class. Responsible for mapping keys and buttons to 
	* commands.
	*/

	virtual ~Command() {}

	/// @brief Executes the action bound to the key. (or button)
	/// @param[in] Pointer to the pawn in which the action is associated with.
	virtual Command* Execute(Pawn* pawn) = 0;

};

class Keys : public Command
{
public:
	Keys* key;
};

class Button : public Command
{
public:
	Button* button;
};
