#include "pch.h"
#include "SpaceShip.h"

SpaceShip::SpaceShip(gef::Platform& platform_, b2World* world_)
	:Pawn(platform_, world_)
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

SpaceShip* SpaceShip::Create(gef::Platform& platform_, b2World* world_)
{
	return new SpaceShip(platform_, world_);
}

void SpaceShip::Update(float delta_time)
{
	Pawn::Update(delta_time);
}
