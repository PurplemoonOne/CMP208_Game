#pragma once

// @brief Base state class, purely virtual.
class State
{
public:

	virtual ~State() {}
	virtual void Input(float delta_time) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render(float delta_time) = 0;

};

