#pragma once
#include "Event.h"

class Jump : public Event
{
public:

	void Action(Pawn* pawn, float delta_time) override
	{

	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{
		Player* player = static_cast<Player*>(animated_pawn);

		if (player)
		{
			player->BroadcastInput(true);

			animated_pawn->GetPhysicsBody()->PhysicsBodyComponent()->ApplyForceToCenter(b2Vec2(0.0f, 10.0f), true);
			
		}

	}

	~Jump(){}

};

