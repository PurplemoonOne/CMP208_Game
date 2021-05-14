#pragma once
#include "GameObjects/GameObject.h"

class MovingPlatform : public GameObject
{
protected:

	MovingPlatform();

public:

	~MovingPlatform();

	// @brief Create a new platform.
	static MovingPlatform* Create();

	// @brief Update the moving platform.
	void Update(float delta_time) override;

	// @brief Function called when colliding with another gameobject.
	void OnCollision(ObjectType type) override;

	// @brief Function called when exiting a collision with another object.
	void EndCollision(ObjectType type) override;

	void SetTargetLocations(b2Vec2 loc_a, b2Vec2 loc_b);

private:

	/*..Attributes..*/
	void Oscillate(float delta_time);

	float impulse;
	uint32 oscillation_switch;
	std::array<b2Vec2, 2> targets;

};

