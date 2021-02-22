#pragma once
/*..Parent header..*/
#include "SceneComponent.h"

/*..graphics headers..*/
#include <graphics/mesh_instance.h>

/*..gef's Transform class..*/
#include <maths/transform.h>

/*..Forward Declarations..*/
namespace gef
{
	class Platform;
	class Renderer3D;
}

/*..Other class dependencies..(NOT internal to gef)..*/
class PrimitiveBuilder;


class GameObject : public SceneComponent, public gef::MeshInstance
{
protected:

	/// @brief Actor constructor.
	/// @param[in] Pointer to a primitive builder
	/// @param[in] Reference to the current platform.
	GameObject(PrimitiveBuilder* primitive_builder, gef::Platform& platform_);
	/// @brief Default constructor.
	~GameObject() {}
public:


	/// @brief Returns a new Actor object which is allocated on to the heap.
	/// @param[in] Pointer to a primitive builder. 
	/// @param[in] Reference to the current platform.
	static GameObject* Create(PrimitiveBuilder* primitive_builder, gef::Platform& platform_);

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	virtual void InitialiseStaticMesh(PrimitiveBuilder* primitive_builder);

	/// @brief Renders this actor.
	/// @param[in] Takes the scene 3D renderer.
	virtual void Render(gef::Renderer3D* renderer);

protected:

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Builds the objects transform 
	virtual void BuildTransform();

	/// @brief Pointer to the current platform.
	gef::Platform* platform_ptr;


private:

	gef::Transform transform_component;

	/// @brief Variable position to hold the actors current position.
	gef::Matrix44 current_position;
	/// @brief Variable rotation to hold the actors current rotation.
	gef::Matrix44 current_rotation;
	/// @brief Variable scale to hold the actors current scale.
	gef::Vector4 current_scale;

};

