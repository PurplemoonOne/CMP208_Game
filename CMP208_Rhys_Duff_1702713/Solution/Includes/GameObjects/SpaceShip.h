#pragma once
#include "Pawn.h"

class SpaceShip final : public Pawn
{
protected:

	SpaceShip(gef::Platform& platform_);

public:

	~SpaceShip();

	static SpaceShip* Create(gef::Platform& platform_);

	/// @brief Updates this objects attributes.
	/// @param[in] Delta time tracks the time since last frame.
	virtual void Update(float delta_time, PhysicsComponent* physics = 0) override;

	// @brief Set the current state of the ship's hull integrity.
	// @pram[in] Takes a floating point value.
	inline void SetShipIntegrity(float value) { hull_integrity = value; }

	// @brief Set the value for the ship's velocity.
	// @pram[in] Takes a floating point value.
	inline void SetShipsVelocity(float value) { velocity = value; }

	// @brief Set the value for the ship's acceleration.
	// @pram[in] Takes a floating point value.
	inline void SetShipAcceleration(float value) { acceleration = value; }

	// @brief Retunrs the pawn's current velocity.
	inline const float& GetVelocity() { return velocity; }

	// @brief Returns the ship's current fuel capacity.
	inline const float& GetFuel() { return fuel; }

	// @brief Returns the pawn's current acceleration.
	inline const float& GetAcceleration() { return acceleration; }

	// @brief Returns the ship's current thrust in newtons.
	inline const float& GetThrust() { return thrust; }

	// @brief Returns the ship's current lifeline.
	inline const float& GetShipIntegrity() { return hull_integrity; }

private:

	/*..Player parameters..*/

	// @brief A meaurement of the ships lifeline.
	float hull_integrity;

	// @brief How much fuel the ship has left.
	float fuel;

	// @brief The rate at which fule is consumed.
	float fuel_loss_rate;

	// @brief How quickly the ship can move in a given direction.
	float velocity;

	// @brief The rate at which the velocity will change with respect to time.
	float acceleration;

	// @brief The force of the thrusters ~tied to the acceleration~.
	float thrust;

};

