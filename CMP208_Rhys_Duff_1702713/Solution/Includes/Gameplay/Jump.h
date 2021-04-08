#pragma once
#include "Event.h"
#include "Physics/PhysicsComponent.h"

class Jump : public Event
{
public:

	void Action(Pawn* pawn, float delta_time) override
	{

	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{
		

	}

	virtual void Action(PhysicsComponent* body, float delta_time)
	{
		Player* player = reinterpret_cast<Player*>(body->PhysicsBody()->GetUserData().pointer);

		if (player)
		{
			if (player->CanJump())
			{
				player->BroadcastInput(true);
				player->SetCanJump(false);

				body->PhysicsBody()->ApplyForceToCenter(b2Vec2(0.0f, 150.0f), true);
			}
		}
	}

	~Jump(){}

};

