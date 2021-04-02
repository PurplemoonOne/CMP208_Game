#include "pch.h"
#include "Asteroid.h"

static uint32_t mesh_instance_count = 0;

Asteroid::Asteroid(gef::Platform& platform_)
	:GameObject(platform_)
{
	mesh_instance_count++;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(float delta_time)
{
}

Asteroid* Asteroid::Create(gef::Platform& platform_)
{
	return new Asteroid(platform_);
}

