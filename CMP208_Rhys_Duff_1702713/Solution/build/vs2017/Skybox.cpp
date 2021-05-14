#include "pch.h"
#include "Skybox.h"

Skybox::Skybox()
    :
    angular_velocity(12.5f)
{
}

Skybox::~Skybox()
{
}

Skybox* Skybox::Create()
{
    return new Skybox();
}

void Skybox::Update(float delta_time)
{
   // float new_rotation = GetRotation().y();
   // new_rotation += angular_velocity * delta_time;
   // SetRotation(GetRotation().x(), new_rotation, GetRotation().z());
   //
    GameObject::Update(delta_time);
}
