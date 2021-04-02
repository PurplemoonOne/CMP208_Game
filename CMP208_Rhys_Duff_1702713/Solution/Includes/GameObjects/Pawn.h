#pragma once
#include "GameObject.h"


namespace gef
{
	class Platform;
}


///A 3D gameobject supporting user input.
class Pawn : public GameObject
{
public:

	/*..Constructor..*/

	/// @brief Constructor for the gameobject.
	/// @param[in] Takes a reference to the current platform.
	/// @param[in] Takes a pointer to the physics world.
	Pawn(gef::Platform& platform_);

	~Pawn();

public:

	/*..Methods public access..*/
	static Pawn* Create(gef::Platform& platform_);

	/// @brief Updates this objects attributes.
	/// @param[in] Delta time tracks the time since last frame.
	virtual void Update(float delta_time) override;

protected:


};

