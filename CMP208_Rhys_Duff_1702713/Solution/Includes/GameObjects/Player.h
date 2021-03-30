#pragma once
#include "AnimatedPawn.h"


class Player : public AnimatedPawn
{
protected:

	Player(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world = 0);

public:

	static Player* Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world = 0);

	void Update(float delta_time) override;
	
	// @brief Return the current health value.
	inline const void SetHealth(float value) { health = value; }
	inline const float& GetHealth() { return health; }

	inline void SetMaxHealth(float value) { max_health = value; }
	inline const float& GetMaxHealth() { return max_health; }

	inline void SetStamina(float value) { stamina = value; }
	inline const float& GetStamina() { return stamina; }

	inline void SetMaxStamina(float value) { max_stamina = value; }
	inline const float& GetMaxStamina() { return max_stamina; }

	inline void SetVelocity(float value) { velocity = value; }
	inline const float& GetVelocity() { return velocity; }

	inline void SetAcceleration(float value) { acceleration = value; }
	inline const float& GetAcceleration() { return acceleration; }

	void BroadcastInput(bool value);
	float current_velocity;

	gef::Animation* walk;
	gef::Animation* idle;

private:

	bool is_moving;


	/*..Player attributes..*/

	float velocity;
	float acceleration;

	float health;
	float max_health;

	float stamina;
	float max_stamina;

	float experience_points;
};

