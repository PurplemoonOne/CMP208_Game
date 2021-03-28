#include "pch.h"
#include "Asteroid.h"

static uint32_t mesh_instance_count = 0;

Asteroid::Asteroid(gef::Platform& platform_, b2World* world_, bool is_dynamic)
	:GameObject(platform_, world_, is_dynamic)
{
	mesh_instance_count++;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(float delta_time)
{
}

Asteroid* Asteroid::Create(gef::Platform& platform_, b2World* world_, bool is_dynamic)
{
	return new Asteroid(platform_, world_, is_dynamic);
}

