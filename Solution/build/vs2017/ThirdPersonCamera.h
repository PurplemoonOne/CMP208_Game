#pragma once

#include "Camera.h"
#include "GameObject.h"

class ThirdPersonCamera : public Camera
{
protected:

	ThirdPersonCamera(gef::Platform* plat);

public:

	~ThirdPersonCamera();


	// @brief returns a new ThirdPersonCamera.
	static ThirdPersonCamera* Create(gef::Platform* platform_);

	/*..Public methods handling input..*/
	void FocusOnObject(GameObject* game_object);

private:


};

