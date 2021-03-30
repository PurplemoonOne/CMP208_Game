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


