#pragma once
#include "GameObjects/GameObject.h"
class Grass : public GameObject
{
protected:

	Grass();

public:

	~Grass();

	static Grass* Create();

	virtual void Update(float delta_time);

	void OnCollision(ObjectType ot) override;
	void EndCollision(ObjectType ot) override;

private:

};

