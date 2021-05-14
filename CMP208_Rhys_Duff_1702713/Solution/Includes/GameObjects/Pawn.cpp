#include "pch.h"
//This file.
#include "Pawn.h"

Pawn::Pawn()
	:
	GameObject()//Pawn is dynamic by default.
{

}

Pawn::~Pawn()
{
}

Pawn* Pawn::Create()
{
	return new Pawn();
}

void Pawn::Update(float delta_time)
{


	GameObject::Update(delta_time);
	//Must call this to ensure GFX is 
	//updated with respect to the physics component.
}

void Pawn::OnCollision(ObjectType ot)
{
}

void Pawn::EndCollision(ObjectType ot)
{
}
