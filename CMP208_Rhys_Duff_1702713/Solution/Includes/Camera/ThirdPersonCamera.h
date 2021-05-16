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

	// @brief Applies a basic camera shake.
	void CameraJitter(float delta_time);

	inline bool& IsShaking() { return is_shaking; }

	inline void SetCanShake(bool value) { can_shake = value; }
	inline bool& CanShake() { return can_shake; }

private:

	void GeneratePointCloud();

	std::vector<gef::Vector4> point_cloud;
	bool is_shaking;
	bool generate_points;
	bool can_shake;
	int index = 0;
};

