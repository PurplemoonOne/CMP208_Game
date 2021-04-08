#include "pch.h"
#include "SplashScreen.h"
#include "Context.h"

#include "system/platform.h"

/*..Asset Loader..*/
#include "Utilities/AssetLoader.h"

SplashScreen::SplashScreen(gef::Platform* platform_)
	:
	track_id(-1)
{
	timer = 0.0f;
	transparency = 0.0f;
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::OnEnter()
{
	gef::ImageData image;
	context->GFXData()->GetAssetLoader()->png_loader.Load("FoundationLogo.png", *context->GetPlatform(), image);

	gef::Texture* texture = gef::Texture::Create(*context->GetPlatform(), image);

	logo.set_texture(texture);
	logo.set_position(0.0f + (context->GetPlatform()->width() / 2.0f), 0.0f + (context->GetPlatform()->height() / 2.0f), 0.0f);
	logo.set_height((float)context->GetPlatform()->height());
	logo.set_width((float)context->GetPlatform()->width());


	track_id = context->GetAudio()->AudioManager()->LoadMusic("Splash.wav", *context->GetPlatform());

	gef::VolumeInfo vol_info;
	vol_info.volume = 100.0f;

	context->GetAudio()->AudioManager()->SetMusicVolumeInfo(vol_info);
	context->GetAudio()->AudioManager()->PlayMusic();
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

	logo.set_height((float)context->GetPlatform()->height());
	logo.set_width((float)context->GetPlatform()->width());


	return true;
}

void SplashScreen::Render()
{
	gef::SpriteRenderer* sprite_renderer = this->context->SpriteRenderer();

	sprite_renderer->Begin(true);

		sprite_renderer->DrawSprite(logo);

	sprite_renderer->End();
}

void SplashScreen::OnExit()
{
	//Re-set some variables.
	timer = 0;
	
	if (logo.texture())
	{
		delete logo.texture();
		logo.set_texture(nullptr);
	}

}
