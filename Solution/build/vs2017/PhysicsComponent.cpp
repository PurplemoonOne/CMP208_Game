#include "pch.h"

#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(b2World* world_, float density, float weight, float friction, bool is_dynamic, float angle, bool is_sensor, float height, float width, gef::Vector4 position_)
{
	world = world_;

	/*..Body's attributes are cloned, hence instantiated on stack..*/
	b2BodyDef body_definition;
	b2FixtureDef fixture_def;
	b2PolygonShape shape;

	/*..Initiliaside the body definition..*/
	if (density > 0.0f) {
		body_definition.type = b2_dynamicBody;
	}
	body_definition.position = b2Vec2(position_.x(), position_.y());
	body_definition.angle = angle;
	body_definition.enabled = true;

	physics_body = world->CreateBody(&body_definition);

	/*..Create our body's shape..*/
	b2Vec2 scale = b2Vec2((width / 2.0f), (height / 2.0f));
	shape.SetAsBox(scale.x, scale.y);

	fixture_def.shape = &shape;
	fixture_def.density = density;
	fixture_def.friction = friction;
	fixture_def.isSensor = is_sensor;

	fixture = physics_body->CreateFixture(&fixture_def);
}


PhysicsComponent::~PhysicsComponent()
{
}
PhysicsComponent* PhysicsComponent::Create(b2World* world_, float density, float weight, float friction, bool is_dynamic, float angle, bool is_sensor, float height, float width,  gef::Vector4 position)
{
	return new  PhysicsComponent(world_, density, weight, friction, is_dynamic, angle, is_sensor, height, width, position);
}
