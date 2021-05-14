#include "pch.h"

#include "PhysicsComponent.h"
#include "Gameobjects/GameObject.h"
#include "GameObjects/AnimatedGameObject.h"

PhysicsComponent::PhysicsComponent(b2World* world_, GameObject* game_object_)
	:
	world(world_),
	game_object(game_object_)
{
	// Need to set the other animated GO to nullptr.
	animated_game_object = nullptr;
	InitialisePhysicsBody();
}

PhysicsComponent::PhysicsComponent(b2World* world_, AnimatedGameObject* game_object_)
	:
	world(world_),
	animated_game_object(game_object_)
{
	game_object = nullptr;
	InitialisePhysicsBody();
}

void PhysicsComponent::Update()
{
	body_position = physics_body->GetPosition();
}


PhysicsComponent::~PhysicsComponent()
{

}
PhysicsComponent* PhysicsComponent::Create(b2World* world_, GameObject* game_object)
{
	return new PhysicsComponent(world_, game_object);
}

PhysicsComponent* PhysicsComponent::Create(b2World* world_, AnimatedGameObject* game_object)
{
	return new PhysicsComponent(world_, game_object);
}

void PhysicsComponent::CreateFixture(Shape shape_, float density, float friction, float mass, bool is_sensor)
{
	/*
	*	In this function, we want to attach a shape to our object, thereby setting the physics body as
	*	the parent AND changing the shapes coordinate system to local. 
	* 
	*	In addition we would like to set various attributes describing how this object behaves in the world.
	*	i.e friction - how resistant is```this object to sliding along a surface
	*
	*/

	b2Filter filter;
	b2FixtureDef fixture_def;
	b2PolygonShape shape;
	b2CircleShape circle;
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
		circle.m_p = b2Vec2(0, 0);
		circle.m_radius = body_scale.x;

		fixture_def.shape = &circle;
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

inline void PhysicsComponent::InitialisePhysicsBody()
{
	if (game_object != nullptr) {
		/*..Grab the position and scale..*/
		body_position = b2Vec2(game_object->GetPosition().x(),
			game_object->GetPosition().y());

			//body_scale = b2Vec2(game_object->GetScale().x() / 2.0f,
			//	game_object->GetScale().y() / 2.0f);	

		body_scale = b2Vec2(0.05f, 0.05f);
	}
	else if (animated_game_object != nullptr) {
		//If we've manually assigned a size ignore the game object's scale.
		
		body_position = b2Vec2(animated_game_object->GetPosition().x(),
			animated_game_object->GetPosition().y());

			body_scale = b2Vec2(animated_game_object->GetScale().x() / 2.0f,
				animated_game_object->GetScale().y() / 2.0f);
			
	}


	b2BodyDef body_definition;

	/*..Initiliaside the body definition..*/
	body_definition.position = b2Vec2(body_position.x, body_position.y);
	body_definition.angle = 0.0f;
	body_definition.enabled = true;


	if (game_object)
	{
		/*..Only want to point to the game object data if the subject is a dynamic body..*/
		body_definition.userData.pointer = reinterpret_cast<uintptr_t>(game_object);
		body_definition.type = (game_object->GetObjectType() == ObjectType::environment_ ? b2_staticBody : b2_dynamicBody);

		if (body_definition.type == b2_dynamicBody || body_definition.type == b2_kinematicBody)
		{
			body_definition.allowSleep = false;
		}
		else
		{
			body_definition.allowSleep = true;
		}
	}
	else if(animated_game_object)
	{
		/*..Only want to point to the game object data if the subject is a dynamic body..*/
		body_definition.userData.pointer = reinterpret_cast<uintptr_t>(animated_game_object);
		body_definition.type = (animated_game_object->GetObjectType() == ObjectType::environment_ ? b2_staticBody : b2_dynamicBody);

		if (body_definition.type == b2_dynamicBody || body_definition.type == b2_kinematicBody)
		{
			body_definition.allowSleep = false;
		}
		else
		{
			body_definition.allowSleep = true;
		}
	}

	/*..Finally create the main physics body for the game object..*/
	physics_body = world->CreateBody(&body_definition);
}
