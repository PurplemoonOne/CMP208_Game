#pragma once
#include "State.h"
#include "graphics/image_data.h"
#include "GameObjects/GameObject.h"
#include "Camera/Camera.h"

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

	//Main menu scene.
	Camera* camera;
	GameObject* tower;

	gef::ImageData image;

	std::array<UIButton*, 6> buttons;

	AssetLoader* asset_loader;

	bool game_state;
	bool options;
	bool exit;

	float session_clock;

};

