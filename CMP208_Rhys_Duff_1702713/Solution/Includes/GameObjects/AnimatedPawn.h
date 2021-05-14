#pragma once
#include "AnimatedGameObject.h"

class AnimatedPawn : public AnimatedGameObject
{
protected:

	AnimatedPawn(const gef::Skeleton& skeleton);

public:

	~AnimatedPawn();

	static AnimatedPawn* Create(const gef::Skeleton& skeleton);

	/*..Standard functions..*/

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;


};

