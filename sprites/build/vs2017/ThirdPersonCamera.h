#pragma once

#include "Camera.h"

class ThirdPersonCamera : public Camera
{
private:

	ThirdPersonCamera(gef::Platform* plat);

public:

	~ThirdPersonCamera();

public:

	static ThirdPersonCamera* Create(gef::Platform* platform_);

	/*..Public methods handling input..*/

	void Input(float delta_time);
	void Update(float delta_time);

private:

	/*..kinematic attributes..*/
	float velocity;
	float acceleration;

	/*..Rotational velocity..*/
	float angular_velocity;

};

