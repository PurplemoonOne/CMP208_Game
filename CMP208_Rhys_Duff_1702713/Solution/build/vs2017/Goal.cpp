#include "pch.h"
#include "Goal.h"

Goal::Goal()
	:
	GameObject(),
	player_contact(false),
	angular_velocity(20.0f)
{
}

Goal::~Goal()
{
}

Goal* Goal::Create()
{
	return new Goal();
}

void Goal::Update(float delta_time)
{
	SetRotation(GetRotation().x(), gef::DegToRad(angular_velocity * delta_time), GetRotation().z());

	GameObject::Update(delta_time);
}

void Goal::OnCollision(ObjectType game_object)
{
	if (game_object == ObjectType::dynamic_pawn_)
	{
	}
}

void Goal::EndCollision(ObjectType game_object)
{
}
