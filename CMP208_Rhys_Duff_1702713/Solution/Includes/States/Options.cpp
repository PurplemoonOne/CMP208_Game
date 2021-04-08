#include "pch.h"
#include "Options.h"
#include "Context.h"
#include "system/platform.h"

Options::Options(gef::Platform* platform)
	:
	backdrop(nullptr),
	back(false),
	button(nullptr)
{
	back = false;

	// Create volume sliders.
	float x_centre = platform->width() / 2.0f;
	float y_positions[] =
	{
		((platform->height() / 2.0f) - (platform->height() / 4.0f)),
		(platform->height() / 2.0f),
		((platform->height() / 2.0f) + (platform->height() / 4.0f))
	};

	AssetLoader* asset_loader = new AssetLoader(*platform);
	float depth = 0.1f;

	std::string tags[] =
	{
		"Master",
		"SFX",
		"Music"
	};

	for (int index = 0; index < 3; ++index)
	{
		Slider* slider = Slider::Create(tags[index], gef::Vector4(x_centre, y_positions[index], 0.1f), depth);
		gef::ImageData slider_img_data;
		slider->set_height(32.0f);
		slider->set_width(32.0f);
		slider->set_position(slider->MaxPosition(), y_positions[index], 0.0f);

		gef::ImageData image_data;
		asset_loader->png_loader.Load("buttons/volume_bg.png", *platform, image_data);
		gef::Texture* texture = gef::Texture::Create(*platform, image_data);
		slider->SetBarBackdrop(texture);
		depth += 0.1f;
		sliders.push_back(slider);
	}


	delete asset_loader;
	asset_loader = nullptr;
}

Options::~Options()
{
	for (auto slider : sliders)
	{
		delete slider;
		slider = nullptr;
	}

	sliders.clear();
	sliders.resize(0);

	CleanSprites();
}

void Options::OnEnter()
{
	gef::Platform* platform = context->GetPlatform();
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();

	float centre_x = ((context->GetPlatform()->width() / 2.0f));
	float depth = 0.1f;

	// Create back button.
	button = UIButton::Create("Back", gef::Vector4(100.0f,
		context->GetPlatform()->height() - (context->GetPlatform()->height() / 8.0f),
		0.1f),
		depth
	);

	
	button->set_texture(asset_loader->Texture("buttons/exit-pressed.png", platform));
	button->set_height(50.0f);
	button->set_width(100.0f);

	//Initialise backdrop.
	backdrop = new gef::Sprite();
	backdrop->set_texture(asset_loader->Texture("forest_background/menu_backdrop.png", platform));
	backdrop->set_height(platform->height() + 512);
	backdrop->set_width(platform->width());
	backdrop->set_position(gef::Vector4(platform->width() / 2.0f, (platform->height() / 2.0f) + 256.0f, 0.2f));

}

void Options::Input(float delta_time)
{
	PawnController* input = context->GetInput();

	input->GetInputManager()->Update();
	input->ProcessTouchInput();

	if (button->IsHover(input) && input->GetMouseData().left_button_state == MouseState::CLICKED)
	{
		back = true;
	}


	for (auto& slider : sliders)
	{
		if (slider->IsHover(input) && input->GetMouseData().left_button_state == MouseState::IS_DOWN)
		{
			slider->UpdatePosition(input->GetMouseData());
		}
	}

}

bool Options::Update(float delta_time)
{
	UpdateVolume();
	for (auto& slider : sliders)
	{
		slider->Update(delta_time);
	}
	
	button->Update(delta_time);
	backdrop->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, (context->GetPlatform()->height() / 2.0f) - 256.0f, 0.2f));

	if (back)
	{
		if (context->GameRunning())
		{
			context->Transition(States::PAUSE);
		}
		else if (!context->GameRunning())
		{
			context->Transition(States::MAIN);
		}
	}

	return true;
}

void Options::Render()
{
	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	sprite_renderer->Begin(true);

		button->Render(sprite_renderer);
		sprite_renderer->DrawSprite(*backdrop);
		
		for (auto& slider : sliders)
		{
			slider->Render(sprite_renderer);
		}

	sprite_renderer->End();

}

void Options::OnExit()
{
	CleanSprites();
	back = false;
}

void Options::UpdateVolume()
{

	for (int index = 0; index < 3; ++index)
	{
		slider_values[index] = sliders[index]->position().x() - sliders[index]->MinPosition();
	}

	float master_volume_percentage = (slider_values[0] / sliders[0]->MaxPosition()) * 100.0f * 2.0f;
	context->GetAudio()->AudioManager()->SetMasterVolume(master_volume_percentage);

	//float sfx_volume_percentage = (slider_values[1] / sliders[1]->MaxPosition()) * 100.0f;
	//gef::VolumeInfo sfx_info;
	//sfx_info.volume = sfx_volume_percentage;
	//context->AudioManager()->SetSampleVoiceVolumeInfo(0, sfx_info);

	//Music volume.
	float music_volume_percentage = (slider_values[2] / sliders[2]->MaxPosition()) * 100.0f;
	context->GetAudio()->SetMusicVolume(music_volume_percentage);

}

void Options::CleanSprites()
{
	if (button)
	{
		delete button;
		button = nullptr;
	}

	if (backdrop)
	{
		delete backdrop;
		backdrop = nullptr;
	}

}
