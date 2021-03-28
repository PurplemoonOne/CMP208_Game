#include "Player.h"

Player::Player(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world)
	:AnimatedPawn(skeleton, platform, world),
	max_health(100.0f),
	health(0.0f),
	max_stamina(100.0f),
	stamina(0.0f),
	velocity(24.0f),
	acceleration(12.0f),
	experience_points(0.0f),
	current_velocity(0.0f)
{
	//Set health
	health = max_health;

	//Set stamina
	stamina = max_stamina;
}

Player* Player::Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world)
{
	return new Player(skeleton, platform, world);
}

void Player::Update(float delta_time)
{
	AnimatedPawn::Update(delta_time);

	if (!is_moving) {
		animation_player->set_clip(idle);
	}

}

void Player::BroadcastInput(bool value)
{
	is_moving = value;
}
