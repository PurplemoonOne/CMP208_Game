#include "GameObject.h"

//System includes.
#include <system/platform.h>

//Primitive Builder
#include "primitive_builder.h"

//Graphics 
#include <graphics/renderer_3d.h>

GameObject::GameObject(PrimitiveBuilder* primitive_builder_, gef::Platform& platform_)
	:SceneComponent(platform_),
	platform_ptr(&platform_)
{
}

void GameObject::Update(float delta_time)
{
}

GameObject* GameObject::Create(PrimitiveBuilder* primitive_builder, gef::Platform& platform_)
{
	return new GameObject(primitive_builder, platform_);
}

void GameObject::InitialiseStaticMesh(PrimitiveBuilder* primitive_builder)
{
	set_mesh(primitive_builder->GetDefaultCubeMesh());

}

void GameObject::Render(gef::Renderer3D* renderer)
{

	renderer->DrawMesh(*this);
}
