#include "pch.h"
#include "AnimatedPawn.h"

AnimatedPawn::AnimatedPawn(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world)
	:
	AnimatedGameObject(skeleton, platform, true, world)
{
}

AnimatedPawn::~AnimatedPawn()
{
}

AnimatedPawn* AnimatedPawn::Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world)
{
	return new AnimatedPawn(skeleton, platform, world);
}


void AnimatedPawn::Update(float delta_time)
{
	AnimatedGameObject::Update(delta_time);
}

