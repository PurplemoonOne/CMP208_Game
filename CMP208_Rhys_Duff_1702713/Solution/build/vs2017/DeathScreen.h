#pragma once
#pragma once
#include "State.h"

/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

/*..Assests..*/
#include "assets/png_loader.h"

// @brief Initial screen displayed on start up.
class DeathScreen : public State
{
public:

	~DeathScreen() {}

	void OnEnter() override;
	void Input(float delta_time) override;
	void Update(float delta_time) override;
	void Render() override;


private:

	// Splash Screen Images.
	gef::Sprite logo;
	gef::ImageData image;

};
