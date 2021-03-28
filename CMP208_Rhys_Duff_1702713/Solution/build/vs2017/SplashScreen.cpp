#include "pch.h"
#include "SplashScreen.h"
#include "Context.h"

#include "system/platform.h"

/*..Asset Loader..*/
#include "AssetLoader.h"

SplashScreen::SplashScreen(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_)
{
	
	sprite_renderer = sprite_renderer_;
	platform = platform_;

	timer = 0.0f;

	asset_loader = new AssetLoader(*platform);//Don't need any 3D mesh.

	gef::ImageData image;
	asset_loader->png_loader.Load("FoundationLogo.png", *platform_, image);

	gef::Texture* texture = gef::Texture::Create(*platform_, image);

	logo.set_texture(texture);
	logo.set_position(0.0f + (platform_->width() / 2.0f),0.0f + (platform_->height() / 2.0f), 0.0f);
	logo.set_height((float)platform_->height());
	logo.set_width((float)platform_->width());

	transparency = 0.0f;
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::OnEnter()
{

}

void SplashScreen::Input(float delta_time)
{
}

bool SplashScreen::Update(float delta_time)
{
	timer += 1.0f * delta_time;

	//After 4 seconds transition to the main menu.
	if (timer >= 4.0f)
	{
		context->Transition(States::MAIN);
	}

	logo.set_height((float)platform->height());
	logo.set_width((float)platform->width());


	return true;
}

void SplashScreen::Render()
{
	sprite_renderer->Begin(true);

		sprite_renderer->DrawSprite(logo);

	sprite_renderer->End();
}

void SplashScreen::OnExit()
{
	//Re-set some variables.
	timer = 0;

	delete asset_loader;
	asset_loader = nullptr;
}
