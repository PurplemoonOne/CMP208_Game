#pragma once
#include "AnimatedGameObject.h"

class AnimatedPawn : public AnimatedGameObject
{
protected:

	AnimatedPawn(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world);

public:

	~AnimatedPawn();

	static AnimatedPawn* Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world);

	/*..Standard functions..*/

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Builds the objects transform 
	//virtual void BuildTransform() override;




private:



};

