#pragma once
#pragma once
#include "Menu.h"

/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

/*..Assests..*/
#include "assets/png_loader.h"

class PawnController;

// @brief Initial screen displayed on start up.
class DeathScreen : public Menu
{
public:

	DeathScreen(gef::Platform* platform_, gef::Renderer3D* renderer_, 
		gef::SpriteRenderer* sprite_renderer_, PawnController* input_);
	~DeathScreen();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit();

private:

	// Splash Screen Images.
	gef::Sprite logo;
	gef::ImageData image;



};
