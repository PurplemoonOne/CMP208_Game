#include "pch.h"

#include "GameObject.h"

/*..Asset Loader..*/
#include "Vendor/AssetLoader.h"

GameObject::GameObject(gef::Platform& platform_, b2World* world_, bool is_dynamic_)

	: SceneComponent(platform_),
	is_dynamic(is_dynamic_),
	platform(&platform_),
	physics_component(nullptr),
	object_type(ObjectType::static_)
{
	position = gef::Vector4::kZero;
	rotation = gef::Vector4::kZero;
	scale = gef::Vector4::kZero;


}

GameObject* GameObject::Create(gef::Platform& platform_, b2World* world_, bool is_dynamic)
{
	return new GameObject(platform_, world_, is_dynamic);
}


void GameObject::AttachPhysicsComponent(b2World* world_)
{
	world_ptr = world_;
	physics_component = PhysicsComponent::Create(world_, this, is_dynamic);
}

void GameObject::InitialisePhysicsFixture(PolyShape shape_, float density, float friction, float mass, bool is_sensor)
{
	//If no friction is applied, assumes to be static.
	if (physics_component)
		physics_component->CreateFixture(shape_, density, friction, mass, is_sensor);

	else
		gef::DebugOut("Error, Create a physics component before attempting to intialise attribute.");
}

void GameObject::Update(float delta_time)
{
	if (physics_component) {
		UpdateMesh();
	}


	//////////////////////////////////////////////////////////
	//Gameplay scripts go here.


	//End
	//////////////////////////////////////////////////////////

	//Build the transform and update the position, rotation and scale.
	BuildTransform();
}

void GameObject::BuildTransform()
{
	//Builds the transform inherited from scene component
	//and updates the transform after any modifications.
	set_transform(GetFinalTransform());
}

inline void GameObject::UpdateMesh()
{
	//We need to update the GFX to reflect the changes made
	//from the simulation.
	physics_component->Update();

	SetPosition(physics_component->PhysicsBodyComponent()->GetPosition().x, 
		physics_component->PhysicsBodyComponent()->GetPosition().y,
		0.0f);
	SetRotation(0.0f, 0.0f, physics_component->PhysicsBodyComponent()->GetAngle());
}

void GameObject::SetMeshAsCube(PrimitiveBuilder* primitive_builder)
{
	//Set the mesh of this object.
	set_mesh(primitive_builder->GetDefaultCubeMesh());
}

void GameObject::SetMeshAsSphere(PrimitiveBuilder* primitive_builder)
{
	set_mesh(primitive_builder->GetDefaultSphereMesh());
}

void GameObject::SetMesh(gef::Mesh* mesh_)
{
	set_mesh(mesh_);
}

