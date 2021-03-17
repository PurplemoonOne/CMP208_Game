#pragma once
#pragma once
#include "State.h"

/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

/*..Assests..*/
#include "assets/png_loader.h"

// @brief Initial screen displayed on start up.
class PauseMenu : public State
{
public:

	~PauseMenu() {}

	void OnEnter() override;
	void Input(float delta_time) override;
	void Update(float delta_time) override;
	void Render() override;


private:

	// Pause menu Screen Images.
	gef::Sprite logo;
	gef::ImageData image;

};
