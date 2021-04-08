#include "pch.h"
#include "SpaceShip.h"

SpaceShip::SpaceShip(gef::Platform& platform_)
	:Pawn(platform_)
{
	hull_integrity = 100.0f;
	velocity = 25.0f;
	acceleration = 1.6f;
	fuel = 100.0f;
	fuel_loss_rate = 0.8f;
	thrust = 10.0f;
}

SpaceShip::~SpaceShip()
{
}

SpaceShip* SpaceShip::Create(gef::Platform& platform_)
{
	return new SpaceShip(platform_);
}

void SpaceShip::Update(float delta_time, PhysicsComponent* physics)
{
	if (physics) {
		UpdateMesh(physics);
	}

	Pawn::Update(delta_time);
}
