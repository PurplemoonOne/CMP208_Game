#pragma once
#include "State.h"
#include "graphics/image_data.h"
#include "GameObjects/GameObject.h"
#include "Camera/Camera.h"
#include "ParallaxBackground.h"

class AssetLoader;
class UIButton;

// @brief Initial screen displayed on start up.
class MainMenu : public State
{
public:

	MainMenu(gef::Platform* platform_);
	~MainMenu();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:

	void LoadButtons();
	void LoadBackdrop();
	void IsMouseHoveringOverButton();
	void UpdateTransition();
	void UpdateButtonTextures();
	void AnimateTitle(float delta_time);

	//Main menu scene.
	gef::Sprite* title;
	std::array<UIButton*, 3> buttons;
	ParallaxBackground* parallax_bg;

	int index;
	float session_clock;
	bool button_pressed;
	bool not_exit;
};

