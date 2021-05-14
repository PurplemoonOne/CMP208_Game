#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(gef::Platform& platform_)
	:
	GameObject(),
	health(100.0f),
	max_health(100.0f),
	velocity(5.0f),
	acceleration(1.2f),
	damage_output(10.0f)
{
}

Enemy::~Enemy()
{
}

Enemy* Enemy::Create(gef::Platform& platform_)
{
	return new Enemy(platform_);
}

void Enemy::Update(float delta_time)
{
	if (physics != nullptr)
	{
		UpdateMesh(physics);
	}


	//Build the transform and update the position, rotation and scale.
	BuildTransform();
}

void Enemy::OnCollision(ObjectType game_object)
{
	if (game_object == ObjectType::dynamic_pawn_)
	{
		UpdateCurrentHealth(-5.0f);
	}
}

void Enemy::EndCollision(ObjectType game_object)
{
}
