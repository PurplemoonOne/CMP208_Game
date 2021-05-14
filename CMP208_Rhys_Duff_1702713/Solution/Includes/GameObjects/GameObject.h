#pragma once
/*..Parent header..*/
#include "SceneComponent.h"

/*..graphics headers..*/
#include <graphics/mesh_instance.h>
#include "Physics/PhysicsComponent.h"
class PhysicsComponent;

#include "ObjectType.h"

/*..Forward Declarations..*/
namespace gef
{
	class Platform;
	class Renderer3D;
	class Scene;
}

/*..Other class dependencies..(NOT internal to gef)..*/
class PrimitiveBuilder;
class AssetLoader;

class GameObject : public SceneComponent, public gef::MeshInstance
{
protected:

	/// @brief Actor constructor.
	/// @param[in] Reference to the current platform.
	GameObject();


public:

	/// @brief Default constructor.
	~GameObject();

	/*..Creation..*/

	/// @brief Returns a new Actor object which is allocated on to the heap.
	/// @param[in] Reference to the current platform.
	static GameObject* Create();

	/*..GFX..*/

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	void SetMeshAsCube(PrimitiveBuilder* primitive_builder);

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	void SetMeshAsSphere(PrimitiveBuilder* primitive_builder);

	// @brief Applies a custom mesh to the object.
	void SetMesh(gef::Mesh* mesh_);

	/*..Standard functions..*/

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Builds the objects transform 
	void BuildTransform();

	/*..Collisions..*/

	virtual void OnCollision(ObjectType game_object);
	virtual void EndCollision(ObjectType game_object);

	// @brief Set the type of game object this is. This will determine what the object can interact with.
	// @param[in] ObjectType Enter the flag this object will endure.
	inline void SetObjectType(ObjectType type) { object_type = type; }

	// @brief returns a const reference to the object type.
	const ObjectType& GetObjectType() const { return object_type; }

	/*..Physics..*/

	// @brief Returns a pointer to the physics object
	inline PhysicsComponent* GetPhysicsBody() const { if (physics) { return physics; } }

	/// @brief Call this to attach a physics component to the game object.
	void AttachPhysicsComponent(b2World* world_);

	// @brief Initialise the characteristics this game object will have.
	// @param[in] The shape of the physics collider.
	// @param[in] The physics body's density
	// @param[in] The amount of friction to act upon this object when sliding against a surface.
	// @param[in] The amount of 'matter' this object will contain, affects force calculations.
	// @param[in] Whether this object is a collider or a trigger. Triggers aren't included in physics calculations.
	void InitialisePhysicsFixture(PhysicsComponent::Shape shape_, float density, float friction, float mass, bool is_sensor);

	inline void SetAlive(bool value) { is_alive = value; }
	inline const bool& IsAlive() { return is_alive; }

	inline void IgnoreZRotation(bool value) { ignore_z_rotation = value; }

protected:

	bool is_alive;
	bool ignore_z_rotation;

	/// @brief Update the GFX on the game object if a physics component is added.
	// @param[in] Takes a pointer to a physics body.
	inline void UpdateMesh(PhysicsComponent* physics_component);

	/*..Protected variables..*/
	ObjectType object_type;

	/// @brief this objects physics component. By default it's NULL.
	//PhysicsComponent* physics_component;

	PrimitiveBuilder* primitive_builder;
	PhysicsComponent* physics;
};
