#include "pch.h"
#include "Player.h"
#include "Vendor/motion_clip_player.h"
#include "Physics/PhysicsComponent.h"

Player::Player(const gef::Skeleton& skeleton)
	:AnimatedPawn(skeleton),
	max_health(100.0f),
	health(0.0f),
	velocity(7.4f),
	acceleration(1.2f),
	experience_points(0.0f),
	current_velocity(0.0f),
	reached_portal(false)
{
	//Set health
	health = max_health;



	score = 0;
}

Player::~Player()
{
}

Player* Player::Create(const gef::Skeleton& skeleton)
{
	return new Player(skeleton);
}

void Player::Update(float delta_time)
{
	AnimatedPawn::Update(delta_time);
	
	if (physics_component) {
		velocity = physics_component->PhysicsBody()->GetLinearVelocity().x;
	}

	if (velocity > -0.1f && velocity < 0.1f) {
		animation_player->set_clip(GetAnimation(AnimationID::idle));
	}
	else if ((velocity >= 0.1f && velocity <= 4.0f) || (velocity < -0.1f && velocity > -4.0f)) {
		animation_player->set_clip(GetAnimation(AnimationID::walk));
	}
	else if (velocity > 4.0f || velocity < -4.0f) {
		animation_player->set_clip(GetAnimation(AnimationID::run));
	}
	if (!can_jump){

		animation_player->set_clip(GetAnimation(AnimationID::fall));
	}

}

void Player::OnCollision(ObjectType game_object)
{
	if (game_object == ObjectType::environment_)
	{
		can_jump = true;
	}

	if (game_object == ObjectType::collectable_)
	{
		score += 1;
	}

	if (game_object == ObjectType::lava_)
	{
		health -= 10.0f;
	}

	if (game_object == ObjectType::gem_)
	{
		score += 3;
	}

	if (game_object == ObjectType::goal_)
	{
		reached_portal = true;
	}
}

void Player::EndCollision(ObjectType game_object)
{


}

void Player::InsertAnimation(AnimationID id, gef::Animation* anim)
{
	animations[(uint32)id] = anim;
}
