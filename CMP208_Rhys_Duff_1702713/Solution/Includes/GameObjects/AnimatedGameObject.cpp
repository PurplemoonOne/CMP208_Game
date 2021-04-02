#include "pch.h"
#include "AnimatedGameObject.h"

/*..Asset Loader..*/
#include "Utilities/AssetLoader.h"

/*..Physics Component..*/
#include "Physics/PhysicsComponent.h"

AnimatedGameObject::AnimatedGameObject(const gef::Skeleton& skeleton_, gef::Platform& platform_)
	:
	SkinnedMeshInstance(skeleton_),
	SceneComponent(platform_),
	skeleton(&skeleton_),
	animation_driver(nullptr)
{
	/*..Create a new motion player to maintain animations..*/
	animation_player = new MotionClipPlayer();
	animation_player->Init(this->bind_pose());
	object_type = ObjectType::environment_dynamic_;

	animation_driver = new AnimDriver();
}

AnimatedGameObject::~AnimatedGameObject()
{
	delete animation_driver;
	animation_driver = nullptr;

	delete animation_player;
	animation_player = nullptr;
}

AnimatedGameObject* AnimatedGameObject::Create(const gef::Skeleton& skeleton, gef::Platform& platform)
{
	return new AnimatedGameObject(skeleton, platform);
}

void AnimatedGameObject::Update(float delta_time)
{


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

//See the header file on why these are commented.
//void AnimatedGameObject::AttachPhysicsComponent(b2World* world_)
//{
//	physics_component = PhysicsComponent::Create(world_, this, is_dynamic);
//}
//
//void AnimatedGameObject::InitialisePhysicsFixture(PolyShape shape_, float density, float friction, float mass, bool is_sensor)
//{
//	if (physics_component)
//		physics_component->CreateFixture(shape_, density, friction, mass, is_sensor);
//
//	else
//		gef::DebugOut("Error, Create a physics component before attempting to intialise attribute.");
//}

inline void AnimatedGameObject::UpdateMesh(PhysicsComponent* physics_component)
{
	//We need to update the GFX to reflect the changes made
	//from the simulation.
	physics_component->Update();

	SetPosition(physics_component->PhysicsBodyComponent()->GetPosition().x,
		physics_component->PhysicsBodyComponent()->GetPosition().y,
		0.0f);
	SetRotation(0.0f, 0.0f, physics_component->PhysicsBodyComponent()->GetAngle());

	BuildTransform();
}

