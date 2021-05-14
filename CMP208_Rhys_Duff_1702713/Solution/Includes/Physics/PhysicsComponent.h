#pragma once
//Box 2D includes
#include "box2d/box2d.h"
#include "maths/vector4.h"

class GameObject;
class AnimatedGameObject;

class PhysicsComponent
{
public:

	/// @brief Simplifies selecting a physics shape.
	enum class Shape
	{
		BOX = 0,
		CIRCLE,
		EDGE,
		POLYGON
	};


	void Update();

protected:

	/*
	*	Physics component.
	*/

	PhysicsComponent(b2World* world_, GameObject* game_object);
	PhysicsComponent(b2World* world_, AnimatedGameObject* game_object);

public:

	~PhysicsComponent();

	/// @brief Returns a new Physics component.
	static PhysicsComponent* Create(b2World* world_, GameObject* game_object);
	static PhysicsComponent* Create(b2World* world_, AnimatedGameObject* game_object);

	/// @brief update the attributes of the physics body.
	/// @param[in] The bodies Denisty.
	/// @param[in] The bodies Friction against a suface, ideal range between '0.0f' and '1.0f'.
	/// @param[in] Is this body a collider or a trigger, i.e collider will react to the simulation where 
	///as a trigger can be used as a means of checking logic.
	void CreateFixture(Shape shape_, float density, float friction, float mass, bool is_sensor);

	/// @brief update the attributes of the physics body.
	/// @param[in] The bodies Denisty.
	/// @param[in] The bodies Weight.
	/// @param[in] The bodies Friction.
	inline void UpdatePhysicsParameters(float density, float weight, float friction);

	/// @brief Returns the objects physics component.
	/// @returns A pointer to the physics body.
	inline b2Body* PhysicsBody() { return physics_body; }



private:

	inline void InitialisePhysicsBody();

	/*..Pointer to the game object that *this* is attached to..*/
	GameObject* game_object;

	AnimatedGameObject* animated_game_object;

	/*..Attributes..*/
	b2Vec2 body_scale;
	b2Vec2 body_position;

	b2World* world = nullptr;
	b2Body* physics_body = nullptr;
	b2Fixture* fixture = nullptr;

};