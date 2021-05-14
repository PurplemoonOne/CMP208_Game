#pragma once
#include "GameObjects/GameObject.h"

class Lava : public GameObject
{
protected:

	Lava();

public:

	~Lava();

	static Lava* Create();

	void Update(float delta_time) override;

	void OnCollision(ObjectType ot) override;
	void EndCollision(ObjectType ot) override;


private:



};

