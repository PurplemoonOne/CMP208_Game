#pragma once
#include "AnimatedPawn.h"

class GameObject;

class Player : public AnimatedPawn
{
protected:

	Player(const gef::Skeleton& skeleton, gef::Platform& platform);

public:

	~Player();

	static Player* Create(const gef::Skeleton& skeleton, gef::Platform& platform);

	void Update(float delta_time, PhysicsComponent* physics = 0) override;
	
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

	inline void SetCanJump(bool value) { can_jump = value; }
	inline const bool& CanJump() { return can_jump; }


	virtual void OnCollision(ObjectType game_object) override;
	virtual void EndCollision(ObjectType game_object) override;


	gef::Animation* walk;
	gef::Animation* idle;
	gef::Animation* jump;

private:

	bool is_moving;
	bool is_airborne;
	bool can_jump;


	/*..Player attributes..*/

	float velocity;
	float acceleration;

	float health;
	float max_health;

	float stamina;
	float max_stamina;

	float experience_points;
};

