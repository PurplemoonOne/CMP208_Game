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
		

	}

	virtual void Action(b2Body* body, float delta_time)
	{
		Player* player = reinterpret_cast<Player*>(body->GetUserData().pointer);

		if (player)
		{
			player->BroadcastInput(true);

			body->ApplyForceToCenter(b2Vec2(0.0f, 10.0f), true);

		}
	}

	~Jump(){}

};

