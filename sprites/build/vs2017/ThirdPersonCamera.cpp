#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(gef::Platform* plat)
	:Camera(plat),
	velocity(0.0f),
	acceleration(0.0f),
	angular_velocity(0.0f)
{
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

ThirdPersonCamera* ThirdPersonCamera::Create(gef::Platform* platform_)
{
	return new ThirdPersonCamera(platform_);
}

void ThirdPersonCamera::Input(float delta_time)
{
}

void ThirdPersonCamera::Update(float delta_time)
{
}
