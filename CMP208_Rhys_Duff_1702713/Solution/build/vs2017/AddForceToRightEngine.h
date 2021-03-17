#pragma once

#include "Event.h"
#include "SpaceShip.h"
#include <system/debug_log.h>


class AddForceToRightEngine : public Event
{
public:


	void Action(Pawn* pawn, float delta_time) override
	{
		//Cast down the class hierarchy to space ship.
		SpaceShip* space_ship = reinterpret_cast<SpaceShip*>(pawn);
		//SpaceShip* space_ship = dynamic_cast<SpaceShip*>(pawn);
		
		if (space_ship)//Check we have the space ship object.
		{
				b2Vec2 right_engine = b2Vec2(pawn->GetPosition().x() + (pawn->GetScale().x() / 2.0f),
					pawn->GetPosition().y() + (pawn->GetScale().y() / 2.0f));

				pawn->GetPhysicsBody()->PhysicsBodyComponent()->ApplyForce(b2Vec2(0.0f, space_ship->GetThrust()),
					right_engine,
					true);
		}
		else
		{
				
				gef::DebugOut("Right engine - Cast to space ship failed.\n");

		}

	
	}


	~AddForceToRightEngine() {}

};
