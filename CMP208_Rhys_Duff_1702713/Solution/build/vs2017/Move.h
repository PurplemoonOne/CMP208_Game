#pragma once
#include "Event.h"
#include "Pawn.h"

#include "Player.h"

#include "maths/math_utils.h"

class MoveRight : public Event
{
public:


	void Action(Pawn* pawn, float delta_time)
	{
		
	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{
	

		Player* player = static_cast<Player*>(animated_pawn);

		if (player)
		{
			player->BroadcastInput(true);

			player->current_velocity += player->GetAcceleration() * delta_time;

			float current_position = 0.0f;
			current_position += player->GetPosition().x() + player->current_velocity * delta_time;

			player->SetPosition(current_position, player->GetPosition().y(), player->GetPosition().z());
			player->SetRotation(0.0f, 180.0f, 0.0f);

			//Change animation.
			player->AnimationPlayer()->set_clip(player->walk);
		}

	}

	~MoveRight(){}
};

class MoveLeft : public Event
{
public:


	void Action(Pawn* pawn, float delta_time)
	{

	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{


		Player* player = static_cast<Player*>(animated_pawn);

		if (player)
		{
			player->BroadcastInput(true);

			player->current_velocity -= player->GetAcceleration() * delta_time;

			float current_position = 0.0f;
			current_position -= player->GetPosition().x() + player->current_velocity * delta_time;

			player->SetPosition(current_position, player->GetPosition().y(), player->GetPosition().z());
			player->SetRotation(0.0f, 180.0f, 0.0f);

			//Change animation.
			player->AnimationPlayer()->set_clip(player->walk);
		}

	}

	~MoveLeft() {}
};
