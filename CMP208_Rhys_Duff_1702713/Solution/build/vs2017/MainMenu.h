#pragma once
#include "Menu.h"


class AssetLoader;
class UIButton;

// @brief Initial screen displayed on start up.
class MainMenu : public Menu
{
public:

	MainMenu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* input_);
	~MainMenu();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:

};

