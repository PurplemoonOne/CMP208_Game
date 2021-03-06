#pragma once

#include "Event.h"
#include "GameObjects/SpaceShip.h"
#include <system/debug_log.h>
#include "Physics/PhysicsComponent.h"

class AddForceToLeftEngine : public Event
{
public:


	void Action(Pawn* pawn, float delta_time) override
	{
		NULL;
	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{
		NULL;
	}

	virtual void Action(PhysicsComponent* body, float delta_time)
	{
		SpaceShip* space_ship = reinterpret_cast<SpaceShip*>(body->PhysicsBody()->GetUserData().pointer);

		if (space_ship)
		{

			b2Vec2 left_engine = b2Vec2(space_ship->GetPosition().x() - (space_ship->GetScale().x() / 2.0f),
				space_ship->GetPosition().y() + (space_ship->GetScale().y() / 2.0f));

			body->PhysicsBody()->ApplyForce(b2Vec2(0.0f,
				space_ship->GetThrust()),
				left_engine,
				true);


		}
	}

	~AddForceToLeftEngine() {}

};

