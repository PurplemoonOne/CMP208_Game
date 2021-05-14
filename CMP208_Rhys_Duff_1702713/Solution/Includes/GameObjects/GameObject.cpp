#include "pch.h"

#include "GameObject.h"

/*..Asset Loader..*/
#include "Utilities/AssetLoader.h"

/*..Physics Component..*/
#include "Physics/PhysicsComponent.h"

GameObject::GameObject()
	: 
	SceneComponent(),
	object_type(ObjectType::static_),
	ignore_z_rotation(false),
	is_alive(true),
	physics(nullptr)
{
	position = gef::Vector4::kZero;
	rotation = gef::Vector4::kZero;
	scale = gef::Vector4::kOne;

}

GameObject::~GameObject()
{
}

GameObject* GameObject::Create()
{
	return new GameObject();
}
 
void GameObject::AttachPhysicsComponent(b2World* world_)
{
	physics = PhysicsComponent::Create(world_, this);
}

void GameObject::InitialisePhysicsFixture(PhysicsComponent::Shape shape_, float density, float friction, float mass, bool is_sensor)
{
	//If no friction is applied, assumes to be static.
	if (physics)
		physics->CreateFixture(shape_, density, friction, mass, is_sensor);

	else
		gef::DebugOut("Error, Create a physics component before attempting to intialise attribute.");
}

void GameObject::Update(float delta_time)
{
	if (physics != nullptr)
	{
		UpdateMesh(physics);
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

void GameObject::OnCollision(ObjectType game_object)
{
}

void GameObject::EndCollision(ObjectType game_object)
{
}

inline void GameObject::UpdateMesh(PhysicsComponent* physics_component)
{
	//We need to update the GFX to reflect the changes made
	//from the simulation.
	physics_component->Update();

	SetPosition(physics_component->PhysicsBody()->GetPosition().x, 
		physics_component->PhysicsBody()->GetPosition().y,
		0.0f);
	if (!ignore_z_rotation) {
		SetRotation(GetRotation().x(), GetRotation().y(), physics_component->PhysicsBody()->GetAngle());
	}
	else {
		SetRotation(GetRotation().x(), GetRotation().y(), GetRotation().z());
	}

}

void GameObject::SetMeshAsCube(PrimitiveBuilder* primitive_builder)
{
	//Set the mesh of this object.
	set_mesh(primitive_builder->GetDefaultCubeMesh());
}

void GameObject::SetMeshAsSphere(PrimitiveBuilder* p)
{
	set_mesh(p->GetDefaultSphereMesh());
}

void GameObject::SetMesh(gef::Mesh* mesh_)
{
	set_mesh(mesh_);
}
