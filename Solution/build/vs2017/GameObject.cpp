#include "pch.h"

#include "GameObject.h"

//System includes.
#include <system/platform.h>
#include <system/debug_log.h>

//Primitive Builder
#include "primitive_builder.h"

//Graphics 
#include <graphics/renderer_3d.h>

//Box2d
#include "box2d/box2d.h"


GameObject::GameObject(gef::Platform& platform_, b2World* world_, bool is_dynamic_)

	: SceneComponent(platform_),
	platform_ptr(&platform_),
	is_dynamic(is_dynamic_),
	platform(&platform_)
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
	if (physics_component)
		physics_component->CreateFixture(shape_, density, friction, mass, is_sensor);

	else
		gef::DebugOut("Error, Create a physics component before attempting to intialise attribute.");
}

bool GameObject::EvaluateStaticMeshInstances()
{

	return false;
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

void GameObject::SetMeshFromDisc(PrimitiveBuilder* primitive_builder, std::string filepath)
{
//	const char* scene_asset_filename = filepath.data();
//	
//		scene_assets_ = LoadSceneAssets(platform_, scene_asset_filename);
//		if (scene_assets_)
//		{
//			mesh_instance_.set_mesh(GetMeshFromSceneAssets(scene_assets_));
//			gef::Matrix44 trans;
//			gef::Matrix44 final_;
//			gef::Matrix44 rotX;
//			trans.SetIdentity();
//			trans.SetTranslation(gef::Vector4(0.0f, -3.0f, 8.0f));
//	
//			rotX.RotationY(90.0f);
//	
//			final_ = rotX * trans;
//	
//			mesh_instance_.set_transform(final_);
//		}
//		else
//		{
//			gef::DebugOut("Scene file %s failed to load\n", scene_asset_filename);
//		}
}


void GameObject::Render(gef::Renderer3D* renderer)
{
	// Draws this object.
	renderer->DrawMesh(*this);
}

//gef::Scene* SceneApp::LoadSceneAssets(gef::Platform& platform, const char* filename)
//{
//	gef::Scene* scene = new gef::Scene();
//
//	if (scene->ReadSceneFromFile(platform, filename))
//	{
//		// if scene file loads successful
//		// create material and mesh resources from the scene data
//		scene->CreateMaterials(platform);
//		scene->CreateMeshes(platform);
//	}
//	else
//	{
//		delete scene;
//		scene = NULL;
//	}
//
//	return scene;
//}
//
//gef::Mesh* SceneApp::GetMeshFromSceneAssets(gef::Scene* scene)
//{
//	gef::Mesh* mesh = NULL;
//
//	// if the scene data contains at least one mesh
//	// return the first mesh
//	if (scene && scene->meshes.size() > 0)
//		mesh = scene->meshes.front();
//
//	return mesh;
//}
//