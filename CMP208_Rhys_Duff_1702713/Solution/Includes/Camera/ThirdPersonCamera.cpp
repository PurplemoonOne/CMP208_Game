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
	camera_target = gef::Vector4(target_.x(), target_.y() + 2.0f, target_.z());
	position = (target_ + gef::Vector4(0.0f, 6.0f, 20.0f));
}


