#include "pch.h"
#include "AnimatedGameObject.h"

AnimatedGameObject::AnimatedGameObject(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world, bool is_dynamic) 
	:
	GameObject(platform, world, is_dynamic),
	SkinnedMeshInstance(skeleton)
{
}

AnimatedGameObject::~AnimatedGameObject()
{
}

AnimatedGameObject* AnimatedGameObject::Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world, bool is_dynamic)
{
	return new AnimatedGameObject(skeleton, platform, world, is_dynamic);
}

void AnimatedGameObject::SetMeshFromDisc(PrimitiveBuilder* primitive_builder, std::string filepath)
{
}

gef::Scene* AnimatedGameObject::LoadSceneAssets(gef::Platform& platform, const char* filename)
{
	return nullptr;
}

void AnimatedGameObject::Render(gef::Renderer3D* renderer)
{
	//renderer->DrawSkinnedMesh((gef::MeshInstance)this, this->bone_matrices(), true);
}

void AnimatedGameObject::Update(float delta_time)
{
}

void AnimatedGameObject::BuildTransform()
{
}
