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
		
		AnimatedGameObject* player = reinterpret_cast<AnimatedGameObject*>(body_a->pointer);
		GameObject* game_object = reinterpret_cast<GameObject*>(body_b->pointer);

		if (body_a)
		{
			if (player && (player->GetObjectType() == ObjectType::dynamic_pawn_))
			{
				if (game_object)
				{
					player->OnCollision(game_object->GetObjectType());
				}
			}
		}
		if (body_b)
		{
			if (game_object)
			{
				if (player)
				{
					game_object->OnCollision(player->GetObjectType());
				}
			}
		}
			
		

	}

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact) override
	{
		b2BodyUserData* body_a = &contact->GetFixtureA()->GetBody()->GetUserData();
		b2BodyUserData* body_b = &contact->GetFixtureB()->GetBody()->GetUserData();

		GameObject* game_object = reinterpret_cast<GameObject*>(body_b->pointer);
		AnimatedGameObject* player = reinterpret_cast<AnimatedGameObject*>(body_a->pointer);

		
		if (body_a)
		{
			if (player && (player->GetObjectType() == ObjectType::dynamic_pawn_))
			{
				player->EndCollision(game_object->GetObjectType());
			}
		}
		if (body_b)
		{
			if (game_object)
			{
				game_object->EndCollision(player->GetObjectType());
			}
		}
		
	}


};

