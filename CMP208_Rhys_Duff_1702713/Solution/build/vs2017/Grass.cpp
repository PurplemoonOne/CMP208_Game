#include "pch.h"
#include "Grass.h"

Grass::Grass()
	:
	GameObject()
{
}

Grass::~Grass()
{
}

Grass* Grass::Create()
{
	return new Grass();
}

void Grass::Update(float delta_time)
{
	GameObject::Update(delta_time);
}

void Grass::OnCollision(ObjectType ot)
{

}

void Grass::EndCollision(ObjectType ot)
{

}
