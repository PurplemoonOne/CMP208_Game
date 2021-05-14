#include "pch.h"
#include "Collectable.h"
#include "Audio.h"

Collectable::Collectable()
	: 
	GameObject(),
	value(1.0f),
	collected(false)
{
}

Collectable* Collectable::Create()
{
	return new Collectable();
}

void Collectable::Update(float delta_time)
{
	if (physics != nullptr)
	{
		UpdateMesh(physics);
	}

	float new_rot = 0.0f;
	new_rot += GetRotation().y() + 5.0f * delta_time;

	SetRotation(GetRotation().x(), new_rot, GetRotation().z());

	if (collected)
	{
		SetAlive(false);
		physics->PhysicsBody()->SetEnabled(false);
	}

	//Build the transform and update the position, rotation and scale.
	BuildTransform();
}

void Collectable::OnCollision(ObjectType game_object)
{
	if (game_object == ObjectType::dynamic_pawn_)
	{
		collected = true;
		audio->PlaySFX(sfxid::coin_sfx, false);
	}
}

void Collectable::EndCollision(ObjectType game_object)
{
	if (game_object == ObjectType::dynamic_pawn_)
	{
		
	}
}
