#pragma once
#include "GameObjects/GameObject.h"

class Skybox : public GameObject
{
protected:

	Skybox();

public:

	~Skybox();

	static Skybox* Create();

	void Update(float delta_time) override;

private:

	float angular_velocity;

};

