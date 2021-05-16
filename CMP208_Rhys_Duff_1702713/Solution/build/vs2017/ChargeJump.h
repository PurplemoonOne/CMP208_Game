#pragma once
#include "Gameplay/Event.h"
#include "Physics/PhysicsComponent.h"
#include "GameObjects/Player.h"

class ChargeJump : public Event
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
				//Grab the current charge.
				float current_charge = player->GetJumpForce();

				//Incriment the charge with respect to time.
				current_charge += 1250.0f * delta_time;

				if (current_charge > 5000.0f) {
					current_charge = 5000.0f;
				}

				//Apply charge to jump.
				player->SetJumpForce(current_charge);

			}
		}
	}

	virtual void Action(PhysicsComponent* body, float delta_time)
	{
		if (body)
		{
			
		}
	}

	~ChargeJump() {}

};