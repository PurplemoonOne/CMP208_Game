#include "pch.h"
#include "Lava.h"

Lava::Lava()
{
}

Lava::~Lava()
{
}

Lava* Lava::Create()
{
    return new Lava();
}

void Lava::Update(float delta_time)
{
}

void Lava::OnCollision(ObjectType ot)
{
}

void Lava::EndCollision(ObjectType ot)
{
}
