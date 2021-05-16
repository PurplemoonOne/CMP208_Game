#pragma once
#include "AnimatedPawn.h"

enum class AnimationID
{
	null = 0,
	idle,
	walk,
	run, 
	jump,
	fall,
	fall_to_roll
};

class Player : public AnimatedPawn
{
protected:

	Player(const gef::Skeleton& skeleton);

public:

	~Player();

	static Player* Create(const gef::Skeleton& skeleton);

	void Update(float delta_time) override;
	
	// @brief Set health.
	// @param[in] Floating point value.
	inline const void SetHealth(float value) { health = value; }
	// @brief Return the current health value.
	inline const float& GetHealth() { return health; }

	// @brief Set the maximum health.
	// @param[in] Floating point value.
	inline void SetMaxHealth(float value) { max_health = value; }
	// @brief Get the maximum health.
	inline const float& GetMaxHealth() { return max_health; }

	// @brief Set the velocity value.
	// @param[in] Floating point value.
	inline void SetVelocity(float value) { velocity = value; }
	inline const float& GetVelocity() { return velocity; }

	inline void SetAcceleration(float value) { acceleration = value; }
	inline const float& GetAcceleration() { return acceleration; }

	float current_velocity;

	// @brief Sets whether the player can jump.
	// @param[in] boolean flag.
	inline void SetCanJump(bool value) { can_jump = value; }

	// @brief Returns the status of jumping.
	inline const bool& CanJump() { return can_jump; }

	inline const int& GetScore(){ return score; }

	inline bool& ReachedPortal() { return reached_portal; }

	virtual void OnCollision(ObjectType game_object) override;
	virtual void EndCollision(ObjectType game_object) override;

	void InsertAnimation(AnimationID id, gef::Animation* anim);
	gef::Animation* GetAnimation(AnimationID id) const { return animations[(uint32)id]; }

	inline void SetJumpForce(float& value) { jump_force = value; }
	const float& GetJumpForce() { return jump_force; }

	// @brief Grabs the air time value.
	inline const float& GetAirTime() { return air_time; }
	inline void ResetAirTime() { air_time = 0.0f; }
private:

	float air_time;

	bool is_moving;
	bool is_airborne;
	bool can_jump;
	bool reached_portal;


	/*..Player attributes..*/

	float velocity;
	float acceleration;

	float health;
	float max_health;

	float jump_force;

	float experience_points;
	int score;

	std::array<gef::Animation*, 7> animations;

	//Animation clips.
	gef::Animation* walk;
	gef::Animation* run;
	gef::Animation* idle;
	gef::Animation* jump;
	gef::Animation* fall;
	gef::Animation* fall_to_roll;
};

