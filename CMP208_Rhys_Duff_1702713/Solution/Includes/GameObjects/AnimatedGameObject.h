#pragma once

/*..Mesh with animations data..*/
#include "graphics/skinned_mesh_instance.h"

/*..Collisions..*/
#include "GameObjects/ObjectType.h"

/*..Base Class..*/
#include "GameObjects/SceneComponent.h"


#include "Animation/AnimDriver.h"

class PhysicsComponent;

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

	AnimatedGameObject(const gef::Skeleton& skeleton, gef::Platform& platform);

public:

	~AnimatedGameObject();

	static AnimatedGameObject* Create(const gef::Skeleton& skeleton, gef::Platform& platform);


	/*..Standard functions..*/

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time, PhysicsComponent* physics = 0) override;

	/// @brief Builds the objects transform 
	virtual void BuildTransform();

	/*..Collisions..*/

	// @brief Set the type of game object this is. This will determine what the object can interact with.
	// @param[in] ObjectType Enter the flag this object will endure.
	inline void SetObjectType(ObjectType type) { object_type = type; }

	// @brief returns a const reference to the object type.
	const ObjectType& GetObjectType() const { return object_type; }


	virtual void OnCollision(ObjectType game_object);
	virtual void EndCollision(ObjectType game_object);

	/*..GFX..*/
	// @brief Applies a custom mesh to the object.
	virtual void SetMesh(gef::Mesh* mesh_);


	/*..Physics..*/


	// @note See the GameObject class on why the following functions remain as comments.


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


	// @brief Returns a pointer to the motion player.
	inline MotionClipPlayer* AnimationPlayer() { return animation_player; }


protected:

	/// @brief Update the GFX on the game object if a physics component is added.
	virtual inline void UpdateMesh(PhysicsComponent* physics_component);


	/*..Protected variables..*/

	ObjectType object_type;

	/// @brief this objects physics component. By default it's NULL.
	//PhysicsComponent* physics_component;

	MotionClipPlayer* animation_player;

	AnimDriver* animation_driver;

	const gef::Skeleton* skeleton;


};

