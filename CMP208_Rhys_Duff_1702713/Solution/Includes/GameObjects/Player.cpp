#include "pch.h"
#include "Player.h"

Player::Player(const gef::Skeleton& skeleton, gef::Platform& platform)
	:AnimatedPawn(skeleton, platform),
	max_health(100.0f),
	health(0.0f),
	max_stamina(100.0f),
	stamina(0.0f),
	velocity(7.4f),
	acceleration(1.2f),
	experience_points(0.0f),
	current_velocity(0.0f)
{
	//Set health
	health = max_health;

	//Set stamina
	stamina = max_stamina;
}

Player::~Player()
{
}

Player* Player::Create(const gef::Skeleton& skeleton, gef::Platform& platform)
{
	return new Player(skeleton, platform);
}

void Player::Update(float delta_time, PhysicsComponent* physics)
{
	AnimatedPawn::Update(delta_time, physics);

	if (!is_moving) {
		animation_player->set_clip(idle);
	}
	if (is_airborne){
		//animation_player->set_clip(jump);
	}

}

void Player::BroadcastInput(bool value)
{
	is_moving = value;
}

void Player::OnCollision(ObjectType game_object)
{
	if (game_object == ObjectType::environment_)
	{
		can_jump = true;
		//	is_airborne = false;
	}
}

void Player::EndCollision(ObjectType game_object)
{
	
}
