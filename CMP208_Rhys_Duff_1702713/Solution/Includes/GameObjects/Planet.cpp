#include "pch.h"
#include "Planet.h"

#include "Vendor/primitive_builder.h"

Planet::Planet(gef::Platform& platform_, float radius_)
	:GameObject(platform_),
	radius(radius_)
{
	SetScale(radius, radius, radius);
}

Planet* Planet::Create(gef::Platform& platform_, float radius)
{
	return new Planet(platform_, radius);
}

void Planet::Update(float delta_time)
{
	//SetRotation(0.0f, 5.0f * delta_time, 0.0f);
}

Planet::~Planet()
{
}
