#pragma once

#include "Event.h"
#include "SpaceShip.h"
#include <system/debug_log.h>


class AddForceToLeftEngine : public Event
{
public:


	void Action(Pawn* pawn, float delta_time) override
	{
		SpaceShip* space_ship = static_cast<SpaceShip*>(pawn);

		if (space_ship)
		{

				b2Vec2 left_engine = b2Vec2(pawn->GetPosition().x() - (pawn->GetScale().x() / 2.0f),
					pawn->GetPosition().y() + (pawn->GetScale().y() / 2.0f));

				pawn->GetPhysicsBody()->PhysicsBodyComponent()->ApplyForce(b2Vec2(0.0f,
					space_ship->GetThrust()),
					left_engine,
					true);


		}
	
	}


	~AddForceToLeftEngine() {}

};

