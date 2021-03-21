#include "pch.h"
#include "SplashScreen.h"
#include "Context.h"

#include "system/platform.h"

SplashScreen::SplashScreen(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, gef::PNGLoader* png_loader_)
{
	
	sprite_renderer = sprite_renderer_;
	platform = platform_;

	timer = 0;
	id = 0;

	gef::ImageData image;
	png_loader_->Load("FoundationLogo.png", *platform_, image);

	gef::Texture* texture = gef::Texture::Create(*platform_, image);

	logo.set_texture(texture);
	logo.set_position(0.0f + (platform_->width() / 2.0f),0.0f + (platform_->height() / 2.0f), 0.0f);
	logo.set_height(platform_->height());
	logo.set_width(platform_->width());
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::OnEnter()
{
	gef::DebugOut("This is the splash screen\n");
}

void SplashScreen::Input(float delta_time)
{
}

void SplashScreen::Update(float delta_time)
{
	timer += 1.0f * delta_time;
	if (timer >= 5.0f)
	{
		context->Transition("Game");
	}

	logo.set_height(platform->height());
	logo.set_width(platform->width());
	//gef::DebugOut("State time : %f\n", timer);
}

void SplashScreen::Render()
{
	sprite_renderer->Begin(true);

		sprite_renderer->DrawSprite(logo);

	sprite_renderer->End();
}

void SplashScreen::OnExit()
{
	gef::DebugOut("Leaving splash screen\n");
	timer = 0;
}
