#pragma once
#include "box2d/b2_world_callbacks.h"
#include "box2d/box2d.h"

#include "system/debug_log.h"

//Class includes
#include "Pawn3d.h"
#include "Asteroid.h"

class ContactListener : public b2ContactListener
{
public:

	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact) override
	{
		b2BodyUserData* object_body_data = &contact->GetFixtureA()->GetBody()->GetUserData();

		if (object_body_data)
		{
			gef::DebugOut("The space ships thrust is ", reinterpret_cast<Pawn*>(object_body_data)->GetThrust());
			gef::DebugOut("\n ");
			gef::DebugOut("The space ships hull integrity ", reinterpret_cast<Pawn*>(object_body_data)->GetShipIntegrity());
			gef::DebugOut("\n ");
			gef::DebugOut("The space ships current velcoity is ", reinterpret_cast<Pawn*>(object_body_data)->GetVelocity());
			gef::DebugOut("\n ");
		}

		b2BodyUserData* object_body_b_data = &contact->GetFixtureB()->GetBody()->GetUserData();

		if (object_body_b_data)
		{
			gef::DebugOut("This asteroid is of type", reinterpret_cast<Asteroid*>(object_body_b_data)->GetObjectType());
			gef::DebugOut("\n ");
		}

	}

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact) override
	{
		gef::DebugOut("No collision is detected!\n");
	}


};

