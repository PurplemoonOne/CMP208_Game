#pragma once
#include "Event.h"
#include "GameObjects/Pawn.h"
#include "GameObjects/Player.h"
#include "Physics/PhysicsComponent.h"

#include "maths/math_utils.h"

class MoveRight : public Event
{
public:


	void Action(Pawn* pawn, float delta_time)
	{
		
	}

	void Action(AnimatedPawn* animated_pawn, float delta_time)
	{

	}

	virtual void Action(PhysicsComponent* body, float delta_time)
	{

		AnimatedGameObject* anim_obj = reinterpret_cast<AnimatedGameObject*>(body->PhysicsBody()->GetUserData().pointer);

		Player* player = static_cast<Player*>(anim_obj);
	
		if (player)
		{
			float force = 0.0f;
			force += (body->PhysicsBody()->GetMass() * player->GetAcceleration() * 0.06f);
			body->PhysicsBody()->ApplyLinearImpulseToCenter(b2Vec2(force, 0.0f), true);

			//Change animation.
			player->AnimationPlayer()->set_clip(player->walk);
			player->SetRotation(0.0f, gef::DegToRad(90.0f), 0.0f);
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

	}

	virtual void Action(PhysicsComponent* body, float delta_time)
	{
		//Grab the animated object associated with this phys component.
		AnimatedGameObject* anim_obj = reinterpret_cast<AnimatedGameObject*>(body->PhysicsBody()->GetUserData().pointer);

		//Try cast to a player object.
		Player* player = static_cast<Player*>(anim_obj);

		if (player)
		{
			float force = 0.0f;
			force += (body->PhysicsBody()->GetMass() * player->GetAcceleration() * -1.0f * 0.06f);
			body->PhysicsBody()->ApplyLinearImpulseToCenter(b2Vec2(force, 0.0f), true);
			
			
			//Change animation.
			player->AnimationPlayer()->set_clip(player->walk);
			player->SetRotation(0.0f, gef::DegToRad(-90.0f), 0.0f);
		}
	}

	~MoveLeft() {}
};
