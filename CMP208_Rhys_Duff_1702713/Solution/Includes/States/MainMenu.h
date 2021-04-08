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

	void LoadButtons();
	
	void SetupCamera();
	void LoadBackdrop();

	void AnimateTitle(float delta_time);

	//Main menu scene.
	Camera* camera;
	std::array<GameObject*, 2> chunks;
	gef::ImageData image;
	gef::Sprite* backdrop;
	gef::Sprite* title;
	std::array<UIButton*, 6> buttons;

	bool game_state;
	bool options;
	bool exit;

	float session_clock;

};

