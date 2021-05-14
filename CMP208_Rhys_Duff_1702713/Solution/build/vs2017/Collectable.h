#pragma once
#include "GameObjects/GameObject.h"

class Audio;

class Collectable : public GameObject
{
protected:

	Collectable();

public:

	static Collectable* Create();


	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	void Update(float delta_time) override;

	/*..Collisions..*/

	// @brief Called when object collides with another gameobject.
	// @param[in] Object type referds to it's collision tag.
	void OnCollision(ObjectType game_object) override;

	// @brief Called on a collision end.
	// @param[in] Takes an object tag.
	void EndCollision(ObjectType game_object) override;

	// @brief Set the numerical value for the collectabe.
	inline void SetValue(float value_) { value = value_; }

	// @brief Return the value for this collectable.
	inline const float& GetValue() { return value; }

	inline void SetAudio(Audio& a) { audio = &a; }

private:

	Audio* audio;

	float value;
	bool collected;
};

