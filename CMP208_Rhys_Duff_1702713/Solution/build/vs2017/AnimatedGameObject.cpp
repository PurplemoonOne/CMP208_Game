#include "pch.h"
#include "AnimatedGameObject.h"

/*..Asset Loader..*/
#include "AssetLoader.h"

AnimatedGameObject::AnimatedGameObject(const gef::Skeleton& skeleton_, gef::Platform& platform_, bool is_dynamic_, b2World* world)
	:
	SkinnedMeshInstance(skeleton_),
	SceneComponent(platform_),
	platform(&platform_),
	skeleton(&skeleton_),
	physics_component(nullptr),
	world_ptr(world),
	is_dynamic(is_dynamic_)
{
	/*..Create a new motion player to maintain animations..*/
	animation_player = new MotionClipPlayer();
	animation_player->Init(this->bind_pose());
	object_type = ObjectType::static_;
}

AnimatedGameObject::~AnimatedGameObject()
{
}

AnimatedGameObject* AnimatedGameObject::Create(const gef::Skeleton& skeleton, gef::Platform& platform, bool is_dynamic, b2World* world)
{
	return new AnimatedGameObject(skeleton, platform, is_dynamic, world);
}

void AnimatedGameObject::Update(float delta_time)
{
	if (physics_component) {
		UpdateMesh();
	}
	

	BuildTransform();
}

void AnimatedGameObject::AnimationUpdate(float delta_time)
{
	// Update the animation player and update to the new pose.
	animation_player->Update(delta_time, this->bind_pose());

	this->UpdateBoneMatrices(animation_player->pose());
}

void AnimatedGameObject::BuildTransform()
{
	set_transform(GetFinalTransform());
}

void AnimatedGameObject::SetMesh(gef::Mesh* mesh_)
{
	set_mesh(mesh_);
}

void AnimatedGameObject::AttachPhysicsComponent(b2World* world_)
{
	world_ptr = world_;
	physics_component = PhysicsComponent::Create(world_, this, is_dynamic);
}

void AnimatedGameObject::InitialisePhysicsFixture(PolyShape shape_, float density, float friction, float mass, bool is_sensor)
{
	if (physics_component)
		physics_component->CreateFixture(shape_, density, friction, mass, is_sensor);

	else
		gef::DebugOut("Error, Create a physics component before attempting to intialise attribute.");
}

inline void AnimatedGameObject::UpdateMesh()
{
	//We need to update the GFX to reflect the changes made
	//from the simulation.
	physics_component->Update();

	SetPosition(physics_component->PhysicsBodyComponent()->GetPosition().x,
		physics_component->PhysicsBodyComponent()->GetPosition().y,
		0.0f);
	SetRotation(0.0f, 0.0f, physics_component->PhysicsBodyComponent()->GetAngle());
}

