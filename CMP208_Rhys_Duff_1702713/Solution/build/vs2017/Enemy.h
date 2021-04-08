#pragma once
#include "GameObjects/GameObject.h"

class Enemy : public GameObject
{
protected:

	// @brief Protected constructor.
	// @param[in] Reference to the platform.
	Enemy(gef::Platform& platform_);

public:

	~Enemy();

	// @brief Create an enemy object.
	// @param[in] Reference to the platform.
	static Enemy* Create(gef::Platform& platform_);

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time, PhysicsComponent* phys_component = 0) override;

	/*..Collisions..*/

	// @brief Called when object collides with another gameobject.
	// @param[in] Object type referds to it's collision tag.
	virtual void OnCollision(ObjectType game_object);

	// @brief Called on a collision end.
	// @param[in] Takes an object tag.
	virtual void EndCollision(ObjectType game_object);

	// @brief Set the enemy's damage out put.
	inline void SetDamageOutput(float value) { damage_output = value; }

	// @brief Returns a reference to the damage output.
	inline const float& GetDamageOutput() { return damage_output; }

	// @brief Set the velocity of the enemy.
	inline void SetVelocity(float value) { velocity = value; }

	// @brief Return a reference to the enemy's velocity
	inline const float& GetVelocity() { return velocity; }

	// @brief Update the value of the enemy's current health.
	inline void UpdateCurrentHealth(float value) { health += value; }

	// @brief Return the current health of the enemy
	inline const float& GetCurrentHealth() { return health; }

	//@brief Set the maximum health for the enemy.
	inline void SetMaxHealth(float value) { max_health = value; }

	//@brief Return the maximum health for an enemy.
	inline const float& GetMaxHealth() { return max_health; }

private:

	/*..Enemy attributes..*/

	float velocity;
	float acceleration;
	float damage_output;
	float health;
	float max_health;

};

