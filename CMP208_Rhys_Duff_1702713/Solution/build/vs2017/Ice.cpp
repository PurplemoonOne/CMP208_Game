#include "pch.h"
#include "Ice.h"

Ice::Ice()
	:
	GameObject(),
	begin_countdown(false),
	lifetime(0.0f)
{
}

Ice::~Ice()
{
}

Ice* Ice::Create()
{
	return new Ice();
}

void Ice::Update(float delta_time)
{
	if (begin_countdown)
	{
		lifetime += 1.0f * delta_time;
	}

	// After 3.0 seconds remove the ice block.
	if (lifetime > 3.0f)
	{
		SetAlive(false);
		physics->PhysicsBody()->SetEnabled(false);
	}

}

void Ice::OnCollision(ObjectType ot)
{
	if (ot == ObjectType::dynamic_pawn_)
	{
		begin_countdown = true;
	}
}

void Ice::EndCollision(ObjectType ot)
{
	if (ot == ObjectType::dynamic_pawn_)
	{
		begin_countdown = false;
		lifetime = 0.0f;
	}
}
