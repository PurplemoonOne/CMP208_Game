#pragma once

class AnimDriver;


class AnimState
{
public:

	virtual ~AnimState() {}

	void SetDriver(AnimDriver* driver)
	{
		this->anim_driver = driver;
	}

	virtual void OnTransition() = 0;
	virtual void Play() = 0;
	virtual void OnExit() = 0;

private:

	AnimDriver* anim_driver;

};