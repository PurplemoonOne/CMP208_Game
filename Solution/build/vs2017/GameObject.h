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

enum class ObjectType
{
	environment_ = 0x0001,
	environment_dynamic_ = 0x0002,
	dynamic_ = 0x0004,
	dynamic_friendly_ = 0x0008,
	dynamic_enemy_ = 0x0010,

};

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

	/*..Creation..*/

	/// @brief Returns a new Actor object which is allocated on to the heap.
	/// @param[in] Pointer to a primitive builder. 
	/// @param[in] Reference to the current platform.
	/// @param[in] Pointer to the world physics object. 
	static GameObject* Create(gef::Platform& platform_, b2World* world_, bool is_dynamic);




	/*..GFX..*/

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	virtual void SetMeshAsCube(PrimitiveBuilder* primitive_builder);

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	/// @param[in] Filepath to the .scn file on disc.
	virtual void SetMeshFromDisc(PrimitiveBuilder* primitive_builder, std::string filepath);




	/*..Standard functions..*/

	/// @brief Renders this actor.
	/// @param[in] Takes the scene 3D renderer.
	virtual void Render(gef::Renderer3D* renderer);

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Builds the objects transform 
	virtual void BuildTransform();




	/*..Collisions..*/

	// @brief Set the type of game object this is. This will determine what the object can interact with.
	// @param[in] ObjectType Enter the flag this object will endure.
	inline void SetObjectType(ObjectType type) { object_type = type; }

	// @brief returns a const reference to the object type.
	const ObjectType& GetObjectType() const { return object_type; }




	/*..Physics..*/

	typedef PhysicsComponent::Shape PolyShape;

	// @brief Returns a pointer to the physics object
	inline PhysicsComponent* GetPhysicsBody() const { if (physics_component) { return physics_component; } }

	/// @brief Call this to attach a physics component to the game object.
	void AttachPhysicsComponent(b2World* world_);

	// @brief Initialise the characteristics this game object will have.
	// @param[in] The shape of the physics collider.
	// @param[in] The physics body's density
	// @param[in] The amount of friction to act upon this object when sliding against a surface.
	// @param[in] The amount of 'matter' this object will contain, affects force calculations.
	// @param[in] Whether this object is a collider or a trigger. Triggers aren't included in physics calculations.
	void InitialisePhysicsFixture(PolyShape shape_, float density, float friction, float mass, bool is_sensor);

protected:

	// @brief The following function handles mesh loading when an object is set to static.
	virtual inline bool EvaluateStaticMeshInstances();

	/// @brief Update the GFX on the game object if a physics component is added.
	inline void UpdateMesh();

	/*..Protected variables..*/

	ObjectType object_type;

	/// @brief Pointer to the current platform.
	gef::Platform* platform_ptr;

	/// @brief this objects physics component. By default it's NULL.
	PhysicsComponent* physics_component = nullptr;

	gef::Platform* platform;


private:

	b2World* world_ptr = nullptr;

	// @brief Setting this true will create a physics component.
	bool is_dynamic = false;

};

