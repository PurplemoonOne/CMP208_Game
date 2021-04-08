#pragma once
#include "input/keyboard.h"

class Pawn;
class b2Body;
class AnimatedPawn;
class State;
class PhysicsComponent;

class Event
{
public:
	/*
	* Base command class. Responsible for mapping keys and buttons to 
	* commands. Purely virtual, (interface) can be overridden.
	*/

	/// @brief Executes the action bound to the key. (or button)
	/// @param[in] Pointer to the pawn in which the action is associated with.
	/// @param[in] Delta time since last frame.
	virtual void Action(Pawn* pawn, float delta_time) = 0;

	/// @brief Executes the action bound to the key. (or button)
	/// @param[in] Pointer to the animated pawn in which the action is associated with.
	/// @param[in] Delta time since last frame.
	virtual void Action(AnimatedPawn* pawn, float delta_time) = 0;

	/// @brief Executes the action bound to the key. (or button)
	/// @param[in] Pointer to the animated pawn in which the action is associated with.
	/// @param[in] Delta time since last frame.
	virtual void Action(PhysicsComponent* pawn, float delta_time) = 0;


	virtual ~Event() {}

};

class Keys 
{
public:
	Event* action;
	bool bound;
};

class Button
{
public:
	Event* action;
	bool bound;
};
