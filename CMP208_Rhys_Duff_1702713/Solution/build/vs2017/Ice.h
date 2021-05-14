#pragma once
#include "GameObjects/GameObject.h"

class Ice : public GameObject
{
protected:

	Ice();

public:

	~Ice();

	static Ice* Create();

	void Update(float delta_time) override;

	void OnCollision(ObjectType ot) override;
	void EndCollision(ObjectType ot) override;

private:

	float lifetime;
	bool begin_countdown;

};

