#pragma once

#include "Camera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/AnimatedGameObject.h"

class ThirdPersonCamera : public Camera
{
protected:

	ThirdPersonCamera(gef::Platform* plat);

public:

	~ThirdPersonCamera();


	// @brief returns a new ThirdPersonCamera.
	static ThirdPersonCamera* Create(gef::Platform* platform_);

	/*..Public methods handling input..*/
	virtual void SetTarget(gef::Vector4 target) override;

private:


};

