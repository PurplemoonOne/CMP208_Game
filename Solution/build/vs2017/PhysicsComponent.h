#pragma once
//Box 2D includes
#include "box2d/box2d.h"
#include "maths/vector4.h"

class PhysicsComponent
{
public:

	/// @brief Simplifies selecting a physics shape.
	enum class Shape
	{
		BOX = 0,
		SPHERE,
		EDGE,
		POLYGON
	};

protected:

	/*
	*	Physics component.
	*/

	PhysicsComponent(b2World* world_,float density, float weight, float friction, bool is_dynamic, float angle, bool is_sensor, float height, float width, gef::Vector4 position);

public:

	~PhysicsComponent();

	/// @brief Returns a new Physics component.
	static PhysicsComponent* Create(b2World* world_, float density, float weight, float friction, bool is_dynamic, float angle, bool is_sensor, float height, float width, gef::Vector4 position);

	/// @brief update the attributes of the physics body.
	/// @param[in] The bodies Denisty.
	/// @param[in] The bodies Weight (in KG).
	/// @param[in] The bodies Friction (in N's)
	//inline void UpdatePhysicsParameters(float density, float weight, float friction);

	/// @brief Returns the objects physics component.
	/// @returns A pointer to the physics body.
	inline b2Body* PhysicsBodyComponent() { return physics_body; }

	///// @brief Sets the world position of the body.
	///// @param[in] Takes a float for the 'x' position.
	///// @param[in] Takes a float for the 'y' position.
	//inline void SetPhysicsBodyPosition(float x_pos, float y_pos);

private:

	b2World* world = nullptr;

	/// @brief The physics component of the game object.
	b2Body* physics_body = nullptr;

	b2Fixture* fixture = nullptr;
	
};