#pragma once
#include "AnimState.h"

enum AnimId
{
	IDLE = 0,
	IDLE_2,
	WALK,
	RUN,
	JUMP,
	FALL,
	FALL_LAND,
	FALL_ROLL
};

class AnimDriver
{
public:

	AnimDriver();
	~AnimDriver();

	void Transition(AnimId state);
	void InsertAnimation(AnimId name, AnimState* state);


	inline AnimState* CurrentAnimState() const { return state; }

protected:

	std::map<AnimId, AnimState*> map;

	AnimState* state;

};