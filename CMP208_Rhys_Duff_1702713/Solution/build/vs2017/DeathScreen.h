#pragma once
#pragma once
#include "State.h"

/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

/*..Assests..*/
#include "assets/png_loader.h"

// @brief Initial screen displayed on start up.
class DeathScreen : public State
{
public:

	DeathScreen(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_);
	~DeathScreen();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual void Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit();

private:

	// Splash Screen Images.
	gef::Sprite logo;
	gef::ImageData image;

};
