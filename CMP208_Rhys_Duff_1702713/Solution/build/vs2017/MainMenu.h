#pragma once
#include "Menu.h"

/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

/*..Assests..*/
#include "assets/png_loader.h"

class UIButton;

// @brief Initial screen displayed on start up.
class MainMenu : public Menu
{
public:

	MainMenu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_,
		gef::PNGLoader* png_loader, PawnController* input_);
	~MainMenu();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:


	bool game_state;
	bool options;
	bool exit;

	float session_clock;

	gef::ImageData image;
	
	std::vector<UIButton*> buttons;
};

