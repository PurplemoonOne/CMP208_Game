#include "pch.h"
#include "Collectable.h"

Collectable::Collectable(gef::Platform& platform_)
	: 
	GameObject(platform_),
	value(1.0f)
{
}

Collectable* Collectable::Create(gef::Platform& platform_)
{
	return new Collectable(platform_);
}

void Collectable::Update(float delta_time, PhysicsComponent* phys_component)
{
	if (phys_component != nullptr)
	{
		UpdateMesh(phys_component);
	}



	//Build the transform and update the position, rotation and scale.
	BuildTransform();
}

void Collectable::OnCollision(ObjectType game_object)
{
}

void Collectable::EndCollision(ObjectType game_object)
{
}
