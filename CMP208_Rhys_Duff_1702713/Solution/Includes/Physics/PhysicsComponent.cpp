#include "pch.h"

#include "PhysicsComponent.h"
#include "Gameobjects/GameObject.h"
#include "GameObjects/AnimatedGameObject.h"

PhysicsComponent::PhysicsComponent(b2World* world_, GameObject* game_object_, bool is_dynamic)
	:world(world_),
	game_object(game_object_)
{
	// Need to set the other animated GO to nullptr.
	// It is kept private and therefore is safe.
	animated_game_object = nullptr;
	InitialisePhysicsBody(is_dynamic);
}

PhysicsComponent::PhysicsComponent(b2World* world_, AnimatedGameObject* game_object_, bool is_dynamic)
	:world(world_),
	animated_game_object(game_object_)
{
	game_object = nullptr;
	InitialisePhysicsBody(is_dynamic);
}

void PhysicsComponent::Update()
{
	body_position = physics_body->GetPosition();
}


PhysicsComponent::~PhysicsComponent()
{
}
PhysicsComponent* PhysicsComponent::Create(b2World* world_, GameObject* game_object, bool is_dynamic)
{
	return new PhysicsComponent(world_, game_object, is_dynamic);
}

PhysicsComponent* PhysicsComponent::Create(b2World* world_, AnimatedGameObject* game_object, bool is_dynamic)
{
	return new PhysicsComponent(world_, game_object, is_dynamic);
}

void PhysicsComponent::CreateFixture(Shape shape_, float density, float friction, float mass, bool is_sensor)
{
	/*
	*	In this function, we want to attach a shape to our object, thereby setting the physics body as
	*	the parent AND changing the shapes coordinate system to local. 
	* 
	*	In addition we would like to set various attributes describing how this object behaves in the world.
	*	i.e friction - how resistant is this object to sliding along a surface
	*
	*/

	b2Filter filter;
	b2FixtureDef fixture_def;
	b2PolygonShape shape;
	b2CircleShape cirlce;
	b2MassData mass_data;

	/*..Create our body's shape..*/
	switch (shape_)
	{
	case Shape::BOX:
		shape.SetAsBox(body_scale.x, body_scale.y);
		/*..Apply the remaining attributes to our body..*/
		fixture_def.shape = &shape;


		break;
	case Shape::EDGE:
		//Make edge.
		break;
	case Shape::POLYGON:
		//Make custom polygon
		break;
	case Shape::CIRCLE:
		cirlce.m_p.Set(body_position.x, body_position.y);
		cirlce.m_radius = (body_scale.x);

		fixture_def.shape = &cirlce;
		break;
	}
	
	fixture_def.density = density;
	fixture_def.friction = friction;
	fixture_def.isSensor = is_sensor;

	/*..Set mass parameters..*/
	mass_data.center = body_position;
	mass_data.mass = mass;


	fixture = physics_body->CreateFixture(&fixture_def);
}

inline void PhysicsComponent::UpdatePhysicsParameters(float density, float weight, float friction)
{
}

inline void PhysicsComponent::InitialisePhysicsBody(bool is_dynamic)
{
	if (game_object != nullptr) {
		/*..Grab the position and scale..*/
		body_position = b2Vec2(game_object->GetPosition().x(),
			game_object->GetPosition().y());

		body_scale = b2Vec2(game_object->GetScale().x() / 2.0f,
			game_object->GetScale().y() / 2.0f);
	}
	else if (animated_game_object != nullptr) {
		
		body_position = b2Vec2(animated_game_object->GetPosition().x(),
			animated_game_object->GetPosition().y());

		body_scale = b2Vec2(animated_game_object->GetScale().x() / 2.0f,
			animated_game_object->GetScale().y() / 2.0f);
	}


	b2BodyDef body_definition;

	/*..Initiliaside the body definition..*/

	is_dynamic ? body_definition.type = b2_dynamicBody : body_definition.type = b2_staticBody;
	body_definition.position = b2Vec2(body_position.x, body_position.y);
	body_definition.angle = 0.0f;
	body_definition.enabled = true;

	if (body_definition.type == b2_dynamicBody || body_definition.type == b2_kinematicBody)
	{
		/*..Only want to point to the game object data if the subject is a dynamic body..*/
		body_definition.userData.pointer = reinterpret_cast<uintptr_t>(game_object);
		body_definition.allowSleep = false;
	}
	else
	{
		body_definition.allowSleep = true;
	}

	/*..Finally create the main physics body for the game object..*/
	physics_body = world->CreateBody(&body_definition);
}
