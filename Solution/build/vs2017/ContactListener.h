#pragma once
#include "box2d/b2_world_callbacks.h"
#include "box2d/box2d.h"

#include "system/debug_log.h"

//Class includes
#include "SpaceShip.h"
#include "Asteroid.h"

class ContactListener : public b2ContactListener
{
public:

	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact) override
	{
		b2BodyUserData* body_a = &contact->GetFixtureA()->GetBody()->GetUserData();

		if (body_a)
		{
			SpaceShip* space_ship = reinterpret_cast<SpaceShip*>(body_a);

			if (space_ship)
			{

				gef::DebugOut("The object type is ", space_ship->GetObjectType());
				gef::DebugOut("\n ");
				gef::DebugOut("The space ships thrust is ", space_ship->GetThrust());
				gef::DebugOut("\n ");
				gef::DebugOut("The space ships hull integrity ", space_ship->GetShipIntegrity());
				gef::DebugOut("\n ");
				gef::DebugOut("The space ships current velcoity is ", space_ship->GetVelocity());
				gef::DebugOut("\n ");

			}
		}

		b2BodyUserData* body_b = &contact->GetFixtureB()->GetBody()->GetUserData();

		if (body_b)
		{
			gef::DebugOut("This asteroid is of type", reinterpret_cast<Asteroid*>(body_b)->GetObjectType());
			gef::DebugOut("\n ");
		}

	}

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact) override
	{
		gef::DebugOut("No collision is detected!\n");
	}


};

