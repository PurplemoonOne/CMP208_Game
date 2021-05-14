#pragma once
#pragma once
#include "State.h"

#include "graphics/image_data.h"

#include "UserInterface/UIButton.h"

class AssetLoader;
class Camera;

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

	void UpdateButtonTextures();

	void IsMouseHoveringOverButton();
	void UpdateTransition();

	std::array<UIButton*, 3> buttons;
	gef::Sprite* backdrop;

	int index;
	float session_clock;
	bool button_pressed;
	bool not_exit;

	void LoadBackdrop();
	void LoadButtons();

};
