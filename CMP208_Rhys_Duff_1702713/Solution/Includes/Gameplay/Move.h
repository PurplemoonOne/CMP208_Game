#pragma once
#include "Event.h"
#include "GameObjects/Pawn.h"

#include "GameObjects/Player.h"

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
			player->SetRotation(0.0f, 90.0f, 0.0f);

			//Change animation.
			player->AnimationPlayer()->set_clip(player->walk);
		}

	}

	virtual void Action(b2Body* body, float delta_time)
	{

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

			player->current_velocity += player->GetAcceleration() * delta_time;

			float current_position = 0.0f;

			current_position += player->GetPosition().x() + player->current_velocity * delta_time * -1;

			player->SetPosition(current_position, player->GetPosition().y(), player->GetPosition().z());
			player->SetRotation(0.0f, -90.0f, 0.0f);

			//Change animation.
			player->AnimationPlayer()->set_clip(player->walk);
		}

	}

	virtual void Action(b2Body* body, float delta_time)
	{

	}

	~MoveLeft() {}
};
