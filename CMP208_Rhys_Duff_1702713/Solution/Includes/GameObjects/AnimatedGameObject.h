#pragma once

/*..Mesh with animations data..*/
#include "graphics/skinned_mesh_instance.h"

/*..Collisions..*/
#include "GameObjects/ObjectType.h"

/*..Base Class..*/
#include "GameObjects/SceneComponent.h"

/*..Physics Component..*/
#include "Physics/PhysicsComponent.h"



#include "Animation/AnimDriver.h"

/*..Forward Declarations..*/
namespace gef
{
	class Platform;
	class Renderer3D;
	class Scene;
}

class AssetLoader;

class AnimatedGameObject : public gef::SkinnedMeshInstance, public SceneComponent
{
protected:

	AnimatedGameObject(const gef::Skeleton& skeleton, gef::Platform& platform, bool is_dynamic, b2World* world = 0);

public:

	~AnimatedGameObject();

	static AnimatedGameObject* Create(const gef::Skeleton& skeleton, gef::Platform& platform, bool is_dynamic, b2World* world = 0);


	/*..Standard functions..*/

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time);

	// @brief Updates the animation.
	// @note seperate function allowing to run on a different thread.
	virtual void AnimationUpdate(float delta_time);

	/// @brief Builds the objects transform 
	virtual void BuildTransform();

	/*..Collisions..*/

	// @brief Set the type of game object this is. This will determine what the object can interact with.
	// @param[in] ObjectType Enter the flag this object will endure.
	inline void SetObjectType(ObjectType type) { object_type = type; }

	// @brief returns a const reference to the object type.
	const ObjectType& GetObjectType() const { return object_type; }

	/*..GFX..*/
	// @brief Applies a custom mesh to the object.
	virtual void SetMesh(gef::Mesh* mesh_);


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

	gef::Scene* asset;

	// @brief Returns a pointer to the motion player.
	inline MotionClipPlayer* AnimationPlayer() { return animation_player; }

protected:

	/// @brief Update the GFX on the game object if a physics component is added.
	inline void UpdateMesh();

	/*..Protected variables..*/

	ObjectType object_type;

	/// @brief this objects physics component. By default it's NULL.
	PhysicsComponent* physics_component;

	gef::Platform* platform;

	MotionClipPlayer* animation_player;

	AnimDriver* animation_driver;

private:

	const gef::Skeleton* skeleton;

	b2World* world_ptr;

	// @brief Setting this true will create a physics component.
	bool is_dynamic;

};

