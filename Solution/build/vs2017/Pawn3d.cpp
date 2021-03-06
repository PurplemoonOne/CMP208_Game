#include "pch.h"
//This file.
#include "Pawn3d.h"

Pawn::Pawn(gef::Platform& platform_, b2World* world_)

	:GameObject(platform_, world_, true)//Pawn is dynamic by default.
{
	controller = nullptr;
}

Pawn::~Pawn()
{
}

Pawn* Pawn::Create(gef::Platform& platform_, b2World* world_)
{
	return new Pawn(platform_, world_);
}

void Pawn::Update(float delta_time)
{
	GameObject::Update(delta_time);//Must call this to ensure GFX is updated with respect to the physics component.



}

void Pawn::BuildTransform()
{
	//May alter this function later.

	set_transform(GetFinalTransform());

}
