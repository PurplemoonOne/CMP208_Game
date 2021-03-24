#include "pch.h"
#include "AnimatedPawn.h"

AnimatedPawn::AnimatedPawn(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world)
	:
	AnimatedGameObject(skeleton, platform, world, true)
{
}

AnimatedPawn::~AnimatedPawn()
{
}

AnimatedPawn* AnimatedPawn::Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world)
{
	return nullptr;
}

void AnimatedPawn::Render(gef::Renderer3D* renderer)
{
}

void AnimatedPawn::Update(float delta_time)
{
}

void AnimatedPawn::BuildTransform()
{
}
