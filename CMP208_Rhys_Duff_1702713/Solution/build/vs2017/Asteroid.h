#pragma once
#include "GameObject.h"

class Asteroid : public GameObject
{
protected:

	// @brief Asteroid object, used as a setting piece and obstacle for the player to void.
	/// @param[in] Reference to the current platform.
	/// @param[in] Pointer to the world physics object. 
	Asteroid(gef::Platform& platform_, b2World* world_, bool is_dynamic);

public:

	~Asteroid();

	/// @brief Renders this actor.
	/// @param[in] Takes the scene 3D renderer.
	virtual void Render(gef::Renderer3D* renderer) override;

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Returns a new Actor object which is allocated on to the heap.
	/// @param[in] Reference to the current platform.
	/// @param[in] Pointer to the world physics object. 
	static Asteroid* Create(gef::Platform& platform_, b2World* world_, bool is_dynamic);

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	/// @param[in] Filepath to the .scn file on disc.
	virtual void SetMeshFromDisc(PrimitiveBuilder* primitive_builder, std::string filepath) override;

	// @brief The following function handles mesh loading when an object is set to static.
	virtual inline bool EvaluateStaticMeshInstances() override;

private:

};

