#pragma once
/*..Parent header..*/
#include "SceneComponent.h"

/*..graphics headers..*/
#include <graphics/mesh_instance.h>

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
	GameObject(gef::Platform& platform_);


public:

	/// @brief Default constructor.
	~GameObject() {}

	/*..Creation..*/

	/// @brief Returns a new Actor object which is allocated on to the heap.
	/// @param[in] Reference to the current platform.
	static GameObject* Create(gef::Platform& platform_);

	/*..GFX..*/

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	virtual void SetMeshAsCube(PrimitiveBuilder* primitive_builder);

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	virtual void SetMeshAsSphere(PrimitiveBuilder* primitive_builder);

	// @brief Applies a custom mesh to the object.
	virtual void SetMesh(gef::Mesh* mesh_);

	/*..Standard functions..*/

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time, PhysicsComponent* phys_component = 0) override;

	/// @brief Builds the objects transform 
	virtual void BuildTransform();

	/*..Collisions..*/

	virtual void OnCollision(ObjectType game_object);
	virtual void EndCollision(ObjectType game_object);

	// @brief Set the type of game object this is. This will determine what the object can interact with.
	// @param[in] ObjectType Enter the flag this object will endure.
	inline void SetObjectType(ObjectType type) { object_type = type; }

	// @brief returns a const reference to the object type.
	const ObjectType& GetObjectType() const { return object_type; }

	/*..Physics..*/


	//----------------------------------Important!--------------------------------------------//
	// @note the following methods have been commented out for peformance reasons. 
	// I thought I would keep them in as well as the definitions to show design iteration.

	// @note Currently the physics components are stored in a vector and pushed in tandem 
	// with the game object vector. This is so they have a 1:1 correlation when it comes to 
	// looping over the objects.
	// Ultimately this is to ensure the data is coalesced improving cache hits speeding the overall process 



	// @brief Returns a pointer to the physics object
	//inline PhysicsComponent* GetPhysicsBody() const { if (physics_component) { return physics_component; } }

	/// @brief Call this to attach a physics component to the game object.
	//void AttachPhysicsComponent(b2World* world_);

	// @brief Initialise the characteristics this game object will have.
	// @param[in] The shape of the physics collider.
	// @param[in] The physics body's density
	// @param[in] The amount of friction to act upon this object when sliding against a surface.
	// @param[in] The amount of 'matter' this object will contain, affects force calculations.
	// @param[in] Whether this object is a collider or a trigger. Triggers aren't included in physics calculations.
	//void InitialisePhysicsFixture(PolyShape shape_, float density, float friction, float mass, bool is_sensor);


protected:

	/// @brief Update the GFX on the game object if a physics component is added.
	// @param[in] Takes a pointer to a physics body.
	inline void UpdateMesh(PhysicsComponent* physics_component);

	/*..Protected variables..*/
	ObjectType object_type;

	/// @brief this objects physics component. By default it's NULL.
	//PhysicsComponent* physics_component;


};

