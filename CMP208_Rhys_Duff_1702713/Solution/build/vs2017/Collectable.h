#pragma once
#include "GameObjects/GameObject.h"

class Collectable : public GameObject
{
protected:

	Collectable(gef::Platform& platform_);

public:

	static Collectable* Create(gef::Platform& platform_);


	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time, PhysicsComponent* phys_component = 0) override;

	/*..Collisions..*/

	// @brief Called when object collides with another gameobject.
	// @param[in] Object type referds to it's collision tag.
	virtual void OnCollision(ObjectType game_object);

	// @brief Called on a collision end.
	// @param[in] Takes an object tag.
	virtual void EndCollision(ObjectType game_object);

	// @brief Set the numerical value for the collectabe.
	inline void SetValue(float value_) { value = value_; }

	// @brief Return the value for this collectable.
	inline const float& GetValue() { return value; }

private:

	float value;

};

