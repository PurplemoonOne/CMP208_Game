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


	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Returns a new Actor object which is allocated on to the heap.
	/// @param[in] Reference to the current platform.
	/// @param[in] Pointer to the world physics object. 
	static Asteroid* Create(gef::Platform& platform_, b2World* world_, bool is_dynamic);

	
private:

};

