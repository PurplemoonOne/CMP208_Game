#include "pch.h"
#include "Planet.h"

#include "primitive_builder.h"

Planet::Planet(gef::Platform& platform_, b2World* world_, float radius_)
	:GameObject(platform_, world_, false),
	radius(radius_)
{
}

Planet* Planet::Create(gef::Platform& platform_, b2World* world_, float radius)
{
	return new Planet(platform_, world_, radius);
}

void Planet::Update(float delta_time)
{
	//SetRotation(0.0f, 5.0f * delta_time, 0.0f);
}

Planet::~Planet()
{
}
