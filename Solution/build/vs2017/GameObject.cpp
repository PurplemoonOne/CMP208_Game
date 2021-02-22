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




	//Build the transform, last thing to call regarding kinematics.
	BuildTransform();
}

void GameObject::BuildTransform()
{
	//Builds the transform inherited from scene component
	//and updates the transform after any modifications.
	set_transform(GetFinalTransform());
}

GameObject* GameObject::Create(PrimitiveBuilder* primitive_builder, gef::Platform& platform_)
{
	return new GameObject(primitive_builder, platform_);
}

void GameObject::InitialiseStaticMesh(PrimitiveBuilder* primitive_builder)
{
	//Set the mesh of this object.
	set_mesh(primitive_builder->GetDefaultCubeMesh());
}

void GameObject::Render(gef::Renderer3D* renderer)
{
	// Draws this object.
	renderer->DrawMesh(*this);
}
