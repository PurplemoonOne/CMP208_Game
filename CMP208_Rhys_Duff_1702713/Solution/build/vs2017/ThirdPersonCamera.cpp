#include "pch.h"
#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(gef::Platform* plat)
	:Camera(plat)
{
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

ThirdPersonCamera* ThirdPersonCamera::Create(gef::Platform* platform_)
{
	return new ThirdPersonCamera(platform_);
}

void ThirdPersonCamera::FocusOnObject(gef::Vector4 target)
{
	position = (target + gef::Vector4(0.0f, 6.0f, 10.0f));
	camera_target = target;
}



