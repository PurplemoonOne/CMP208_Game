//This file.
#include "Pawn3d.h"

Pawn::Pawn(PrimitiveBuilder* primitive_builder_, gef::Platform& platform_)
	:GameObject(primitive_builder_, platform_)
{
	controller = nullptr;
}

Pawn::~Pawn()
{
}

Pawn* Pawn::Create(PrimitiveBuilder* primitive_builder, gef::Platform& platform_)
{
	return new Pawn(primitive_builder, platform_);
}

void Pawn::Update(float delta_time)
{
	SceneComponent::Update(delta_time);

}

void Pawn::BuildTransform()
{
	//May alter this function later.

	set_transform(GetFinalTransform());

}
