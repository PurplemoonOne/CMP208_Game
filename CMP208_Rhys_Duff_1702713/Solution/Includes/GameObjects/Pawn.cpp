#include "pch.h"
//This file.
#include "Pawn.h"

Pawn::Pawn(gef::Platform& platform_)
	:
	GameObject(platform_)//Pawn is dynamic by default.
{

}

Pawn::~Pawn()
{
}

Pawn* Pawn::Create(gef::Platform& platform_)
{
	return new Pawn(platform_);
}

void Pawn::Update(float delta_time, PhysicsComponent* physics)
{


	GameObject::Update(delta_time);
	//Must call this to ensure GFX is 
	//updated with respect to the physics component.
}
