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

void ThirdPersonCamera::SetTarget(gef::Vector4 target_)
{
	camera_target = target_;
	position = (target_ + gef::Vector4(-2.0f, 6.0f, 10.0f));
}


