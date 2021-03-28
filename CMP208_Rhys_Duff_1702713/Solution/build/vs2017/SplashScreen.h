#pragma once
#include "State.h"

/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

class AssetLoader;

// @brief Initial screen displayed on start up.
class SplashScreen : public State
{
public:

	// @brief Simply displays and image for a few seconds.
	  SplashScreen(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_);
	  ~SplashScreen();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:

	float transparency;

	// Splash Screen Images.
	gef::Sprite logo;

	gef::Platform* platform;

	gef::SpriteRenderer* sprite_renderer;

	AssetLoader* asset_loader;

	float timer;
};

