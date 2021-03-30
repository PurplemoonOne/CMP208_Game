#pragma once
#pragma once
#include "State.h"

#include "graphics/image_data.h"

#include "UserInterface/UIButton.h"

class AssetLoader;

// @brief Initial screen displayed on start up.
class PauseMenu : public State
{
public:

	PauseMenu(gef::Platform* platform_);
	~PauseMenu();

	virtual void OnEnter() override;
	virtual void Input(float delta_time)  override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:

	gef::ImageData image;

	std::vector<UIButton*> buttons;

	bool game_state;
	bool options;
	bool exit;

	float session_clock;
};
