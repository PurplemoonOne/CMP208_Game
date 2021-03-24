#include "pch.h"
#include "AnimatedGameObject.h"

/*..Asset Loader..*/
#include "AssetLoader.h"

AnimatedGameObject::AnimatedGameObject(const gef::Skeleton& skeleton_, gef::Platform& platform_, b2World* world, bool is_dynamic) 
	:
	platform(&platform_),
	skeleton(&skeleton_),
	SkinnedMeshInstance(*skeleton),
	SceneComponent(*platform),
	object_type(ObjectType::dynamic_),
	physics_component(nullptr)
{
	/*..Create a new motion player to maintain animations..*/
	animation_player = new MotionClipPlayer();
	animation_player->Init(this->bind_pose());
}

AnimatedGameObject::~AnimatedGameObject()
{
}

AnimatedGameObject* AnimatedGameObject::Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world, bool is_dynamic)
{
	return new AnimatedGameObject(skeleton, platform, world, is_dynamic);
}

void AnimatedGameObject::SetMeshFromDisc(AssetLoader* asset_loader, std::string filename)
{
	set_mesh(asset_loader->LoadMesh(filename));
}


void AnimatedGameObject::Render(gef::Renderer3D* renderer)
{
	renderer->DrawSkinnedMesh(*this, this->bone_matrices(), true);
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

