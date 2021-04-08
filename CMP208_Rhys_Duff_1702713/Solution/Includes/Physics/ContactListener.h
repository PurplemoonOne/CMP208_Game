#pragma once
#include "box2d/b2_world_callbacks.h"
#include "box2d/box2d.h"

#include "system/debug_log.h"

//Class includes
#include "Gameobjects/player.h"

class ContactListener : public b2ContactListener
{
public:

	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact) override
	{
		b2BodyUserData* body_a = &contact->GetFixtureA()->GetBody()->GetUserData();
		b2BodyUserData* body_b = &contact->GetFixtureB()->GetBody()->GetUserData();

		/*..jumping checks..*/
		
			GameObject* player = reinterpret_cast<GameObject*>(body_a->pointer);
			GameObject* floor = reinterpret_cast<GameObject*>(body_b->pointer);

			if (player)
			{
				if (floor)
				{
					player->OnCollision(floor->GetObjectType());
				}
			}
		
			if (floor)
			{
				if (player)
				{
					player->OnCollision(floor->GetObjectType());
				}
			}
	}

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact) override
	{
		b2BodyUserData* body_a = &contact->GetFixtureA()->GetBody()->GetUserData();
		b2BodyUserData* body_b = &contact->GetFixtureB()->GetBody()->GetUserData();

		/*..jumping checks..*/
		if (body_a)
		{
			Player* player = reinterpret_cast<Player*>(body_a->pointer);

			if (player)
			{
				if (body_b)
				{
					GameObject* floor = reinterpret_cast<GameObject*>(body_b->pointer);
					if (floor)
					{
 						player->EndCollision(floor->GetObjectType());
					}
				}
			}
		}

		if (body_b)
		{
			GameObject* floor = reinterpret_cast<GameObject*>(body_b->pointer);

			if (floor)
			{
				if (body_a)
				{
					Player* player = reinterpret_cast<Player*>(body_a->pointer);
					if (player)
					{
						player->EndCollision(floor->GetObjectType());
					}
				}
			}
		}



	}


};

