#pragma once
#include "AnimState.h"

class WalkAnim : public AnimState
{
public:

	WalkAnim();
	~WalkAnim();

	virtual void OnTransition() override;
	virtual void Play() override;
	virtual void OnExit() override;



private:



};