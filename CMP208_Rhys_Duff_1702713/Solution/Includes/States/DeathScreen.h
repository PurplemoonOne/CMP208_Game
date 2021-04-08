#pragma once
#include "State.h"
/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

/*..Assests..*/
#include "assets/png_loader.h"

class PawnController;
class UIButton;

// @brief Initial screen displayed on start up.
class DeathScreen : public State
{
public:

	DeathScreen(gef::Platform* platform_);
	~DeathScreen();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:


	gef::ImageData image;
	std::array<UIButton*, 4> buttons;

	bool game_state;
	bool exit;

	float session_clock;
};
