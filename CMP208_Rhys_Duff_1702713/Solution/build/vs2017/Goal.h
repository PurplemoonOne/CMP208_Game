#pragma once
#include "GameObjects/GameObject.h"

class Goal : public GameObject
{
protected:


	Goal();


public:

	~Goal();

	static Goal* Create();

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/*..Collisions..*/

	virtual void OnCollision(ObjectType game_object) override;
	virtual void EndCollision(ObjectType game_object) override;

	inline const bool& Contact() { return player_contact; }

private:

	bool player_contact;
	float angular_velocity;
};

