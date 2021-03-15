#pragma once

// @brief Base state class, purely virtual.
class State
{
public:

	virtual ~State();
	virtual Input(float delta_time);

};

