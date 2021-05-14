#include "pch.h"
#include "AnimatedPawn.h"

AnimatedPawn::AnimatedPawn(const gef::Skeleton& skeleton)
	:
	AnimatedGameObject(skeleton)
{
}

AnimatedPawn::~AnimatedPawn()
{
}

AnimatedPawn* AnimatedPawn::Create(const gef::Skeleton& skeleton)
{
	return new AnimatedPawn(skeleton);
}


void AnimatedPawn::Update(float delta_time)
{



	AnimatedGameObject::Update(delta_time);
}

