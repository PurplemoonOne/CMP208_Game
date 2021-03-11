#pragma once
#include "GameObject.h"

namespace gef
{
	
}

class Planet : public GameObject
{
protected:

	// @brief Protected planet constructor.
	// @param[in] Takes a pointer to the scene's primitive builder for instantiating mesh.
	// @param[in] Takes a reference to the current platform.
	// @param[in] A pointer to the physics world for simulating physics.
	// @param[in] The planet's radius.
	Planet(gef::Platform& platform_, b2World* world_, float radius = 1.0f);

public:

	// @brief Instantiate a planet object for the game world.
	// @param[in] Takes a pointer to the scene's primitive builder for instantiating mesh.
	// @param[in] Takes a reference to the current platform.
	// @param[in] A pointer to the physics world for simulating physics.
	// @param[in] The planet's radius.
	static Planet* Create(gef::Platform& platform_, b2World* world_, float radius = 1.0f);

	// @brief Updates the planet's attributes.
	// @param[in] Delta time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	virtual void SetMeshSphere(PrimitiveBuilder* primitive_builder);

	~Planet();

private:

	/*..Planet Attributes..*/
	float radius;

};

