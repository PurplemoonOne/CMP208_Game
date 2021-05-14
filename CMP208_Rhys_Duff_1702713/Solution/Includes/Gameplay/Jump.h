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
		if (animated_pawn)
		{
			Player* player = reinterpret_cast<Player*>(animated_pawn);

			if (player)
			{
				if (player->CanJump())
				{
					player->SetCanJump(false);
					player->GetPhysicsBody()->PhysicsBody()->ApplyForceToCenter(b2Vec2(0.0f, 1000.0f), true);
				}
			}
		}
	}

	virtual void Action(PhysicsComponent* body, float delta_time)
	{
		if (body)
		{
			Player* player = reinterpret_cast<Player*>(body->PhysicsBody()->GetUserData().pointer);

			if (player)
			{
				if (player->CanJump())
				{
					player->SetCanJump(false);
					body->PhysicsBody()->ApplyForceToCenter(b2Vec2(0.0f, 100.0f), true);
				}
			}
		}
	}

	~Jump(){}

};

