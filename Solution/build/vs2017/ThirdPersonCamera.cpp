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

void ThirdPersonCamera::FocusOnObject(GameObject* game_object)
{

	camera_target = gef::Vector4(game_object->GetPosition().x(), game_object->GetPosition().y(), game_object->GetPosition().z());
	//camera_up = gef::Vector4(game_object->GetPosition().x(), game_object->GetPosition().y(), game_object->GetPosition().z());

}

