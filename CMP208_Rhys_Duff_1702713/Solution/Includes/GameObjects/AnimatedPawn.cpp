#include "pch.h"
#include "AnimatedPawn.h"

AnimatedPawn::AnimatedPawn(const gef::Skeleton& skeleton, gef::Platform& platform)
	:
	AnimatedGameObject(skeleton, platform)
{
}

AnimatedPawn::~AnimatedPawn()
{
}

AnimatedPawn* AnimatedPawn::Create(const gef::Skeleton& skeleton, gef::Platform& platform)
{
	return new AnimatedPawn(skeleton, platform);
}


void AnimatedPawn::Update(float delta_time)
{
	AnimatedGameObject::Update(delta_time);
}

