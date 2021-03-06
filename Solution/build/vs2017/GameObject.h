#pragma once
/*..Parent header..*/
#include "SceneComponent.h"

/*..graphics headers..*/
#include <graphics/mesh_instance.h>

/*..gef's Transform class..*/
#include <maths/transform.h>

/*..Physics Component..*/
#include "PhysicsComponent.h"



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
	/// @param[in] Dictates whether the game object is dynamic at construction time.
	GameObject(gef::Platform& platform_, b2World* world_, bool is_dynamic);


	/// @brief Default constructor.
	~GameObject() {}
public:

	// @brief Overrides the parent setter. Now we need to update the physics body's position rather than the mesh. GFX is updated in UpdateMesh anyway.
	// @param[in] Position 'x'
	// @param[in] Position 'y'
	// @param[in] Position 'z'
	//virtual void SetPosition(float x_pos, float y_pos, float z_pos) override;

	/// @brief Returns a new Actor object which is allocated on to the heap.
	/// @param[in] Pointer to a primitive builder. 
	/// @param[in] Reference to the current platform.
	/// @param[in] Pointer to the world physics object. 
	static GameObject* Create(gef::Platform& platform_, b2World* world_, bool is_dynamic);

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	virtual void InitialiseStaticMesh(PrimitiveBuilder* primitive_builder);


	/// @brief Renders this actor.
	/// @param[in] Takes the scene 3D renderer.
	virtual void Render(gef::Renderer3D* renderer);

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	inline PhysicsComponent* GetPhysicsBody() const { if (physics_component) { return physics_component; } }

protected:

	/// @brief Builds the objects transform 
	virtual void BuildTransform();

	/// @brief Pointer to the current platform.
	gef::Platform* platform_ptr;

protected:

	/// @brief Update the GFX on the game object if a physics component is added.
	inline void UpdateMesh();

	/// @brief this objects physics component. By default it's NULL.
	PhysicsComponent* physics_component = nullptr;

public:

	/// @brief Call this to attach a physics component to the game object.
	void AttachPhysicsComponent(b2World* world_);

	typedef PhysicsComponent::Shape PolyShape;

	void InitialisePhysicsFixture(PolyShape shape_, float density, float friction, float mass, bool is_sensor);

private:

	// @brief Setting this true will create a physics component.
	bool is_dynamic = false;

//
//	/// @brief Variable position to hold the actors current position.
//	gef::Matrix44 current_position;
//	/// @brief Variable rotation to hold the actors current rotation.
//	gef::Matrix44 current_rotation;
//	/// @brief Variable scale to hold the actors current scale.
//	gef::Vector4 current_scale;

};

