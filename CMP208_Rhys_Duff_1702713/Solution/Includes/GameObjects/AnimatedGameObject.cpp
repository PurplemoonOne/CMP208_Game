#include "pch.h"
#include "AnimatedGameObject.h"

/*..Asset Loader..*/
#include "Utilities/AssetLoader.h"

/*..Physics Component..*/
#include "Physics/PhysicsComponent.h"

#include "Vendor/motion_clip_player.h"

AnimatedGameObject::AnimatedGameObject(const gef::Skeleton& skeleton_)
	:
	SkinnedMeshInstance(skeleton_),
	SceneComponent(),
	skeleton(&skeleton_),
	ignore_z_rotation(false),
	is_alive(true)
{
	/*..Create a new motion player to maintain animations..*/
	animation_player = new MotionClipPlayer();
	animation_player->Init(this->bind_pose());

}

AnimatedGameObject::~AnimatedGameObject()
{

	delete animation_player;
	animation_player = nullptr;
}

AnimatedGameObject* AnimatedGameObject::Create(const gef::Skeleton& skeleton)
{
	return new AnimatedGameObject(skeleton);
}


void AnimatedGameObject::Update(float delta_time)
{
	if(physics_component) {
		UpdateMesh(physics_component);
	}

	// Update the animation player and update to the new pose.
	animation_player->Update(delta_time, this->bind_pose());
	this->UpdateBoneMatrices(animation_player->pose());

	BuildTransform();
}

void AnimatedGameObject::BuildTransform()
{
	set_transform(GetFinalTransform());
}

void AnimatedGameObject::OnCollision(ObjectType game_object)
{

}

void AnimatedGameObject::EndCollision(ObjectType game_object)
{
}

void AnimatedGameObject::SetMesh(gef::Mesh* mesh_)
{
	set_mesh(mesh_);
}

void AnimatedGameObject::AttachPhysicsComponent(b2World* world_)
{
	physics_component = PhysicsComponent::Create(world_, this);
}

void AnimatedGameObject::InitialisePhysicsFixture(PhysicsComponent::Shape shape_, float density, float friction, float mass, bool is_sensor)
{
	if (physics_component)
		physics_component->CreateFixture(shape_, density, friction, mass, is_sensor);

	else
		gef::DebugOut("Error, Create a physics component before attempting to intialise attribute.");
}

inline void AnimatedGameObject::UpdateMesh(PhysicsComponent* physics)
{
	//We need to update the GFX to reflect the changes made
	//from the simulation.
	if (physics_component)
	{
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
	BuildTransform();
}

