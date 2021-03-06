#pragma once

#include "Event.h"
#include "Pawn3d.h"
#include "GameObject.h"


class AddForceToRightEngine : public Event
{
public:


	void Action(Pawn* pawn, float delta_time) override
	{
		b2Vec2 right_engine = b2Vec2(pawn->GetPosition().x() + (pawn->GetScale().x() / 2.0f),
			pawn->GetPosition().y() + (pawn->GetScale().y() / 2.0f));

		pawn->GetPhysicsBody()->PhysicsBodyComponent()->ApplyForce(b2Vec2(0.0f, 10.0f), right_engine, true);
	}


	~AddForceToRightEngine() {}

};

