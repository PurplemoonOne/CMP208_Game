#include "pch.h"
#include "Options.h"
#include "Context.h"
#include "system/platform.h"
#include "input/sony_controller_input_manager.h"
#include "ParallaxBackground.h"

Options::Options(gef::Platform* platform)
	:
	parallax_bg(nullptr),
	back(false),
	button(nullptr),
	index(0)
{
	option_text.fill(nullptr);
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
	button = UIButton::Create("Back", gef::Vector4(context->GetPlatform()->width() / 8.0f,	 //	:-	X
		context->GetPlatform()->height() - (context->GetPlatform()->height() / 8.0f),		 //	:-	Y
		-0.2f)																				 //	:-	Z
	);

	//Get the texture stored in the GFX data class.
	button->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Exit_Pressed));
	button->set_height(50.0f);
	button->set_width(100.0f);

	parallax_bg = ParallaxBackground::Create(platform, context->GFXData());
	InitSliders();

	/*..Initialise the font..*/
	for (auto& font : option_text)
	{
		if (!font)
		{
			font = new gef::Font(*context->GetPlatform());
			font->Load("comic_sans");
		}
	}

}

void Options::Input(float delta_time)
{
	PawnController* input = context->GetInput();

	input->GetInputManager()->Update(); //Update the input.
	input->ProcessTouchInput();

	// Simple input processing : check which state we wish to enter.
	const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();

	if (input->ControllerActive())
	{
		if (sce_manger)
		{
			const gef::SonyController* controller = sce_manger->GetController(0);

			if (controller)
			{
				if (controller->buttons_down() == gef_SONY_CTRL_DOWN)
				{
					sliders[index]->IsSelected(false);
					index = (index == (sliders.size() - 1)) ? 0 : index + 1;
				}
				else if (controller->buttons_down() == gef_SONY_CTRL_UP)
				{
					sliders[index]->IsSelected(false);
					index = (index == 0) ? (sliders.size() - 1) : index - 1;
				}

				sliders[index]->IsSelected(true);

				if (controller->buttons_pressed() == gef_SONY_CTRL_RIGHT)
				{
					sliders[index]->UpdatePosition(input->GetMouseData(), 20.0f);
				}
				else if (controller->buttons_pressed() == gef_SONY_CTRL_LEFT)
				{
					sliders[index]->UpdatePosition(input->GetMouseData(), -20.0f);
				}

			}
		}
	}
	else
	{
		for (auto& slider : sliders)
		{
			if (slider->IsHover(input, context->GetAudio()) && input->GetMouseData().left_button_state == MouseState::IS_DOWN)
			{
				slider->UpdatePosition(input->GetMouseData(), 0.0f);
			}
		}
	}

	EvalButton();
}

bool Options::Update(float delta_time)
{
	UpdateVolume();
	for (auto& slider : sliders)
	{
		slider->Update(delta_time);
	}
	
	button->Update(delta_time);
	parallax_bg->UpdateMenuVersion(delta_time);

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

	parallax_bg->Render(sprite_renderer);

		RenderFont();
		button->Render(sprite_renderer);
		
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

	float master_volume_percentage = (slider_values[0] / sliders[0]->MaxPosition()) * 100.0f * 3.0f;
	context->GetAudio()->AudioManager()->SetMasterVolume(master_volume_percentage);

	float sfx_volume_percentage = (slider_values[1] / sliders[1]->MaxPosition()) * 100.0f;
	gef::VolumeInfo sfx_info;
	sfx_info.volume = sfx_volume_percentage;
	context->GetAudio()->SetSFXVolume(sfx_volume_percentage);

	//Music volume.
	float music_volume_percentage = (slider_values[2] / sliders[2]->MaxPosition()) * 100.0f * 3.0f;
	context->GetAudio()->SetMusicVolume(music_volume_percentage);

}

void Options::CleanSprites()
{
	//Remove button data and 
	//supporting text.
	if (button)
	{
		delete button;
		button = nullptr;
	}

	if (parallax_bg)
	{
		delete parallax_bg;
		parallax_bg = nullptr;
	}

	for (auto& font : option_text)
	{
		if (font)
		{
			delete font;
			font = nullptr;
		}
	}

}

void Options::EvalButton()
{
	PawnController* input = context->GetInput();

	if (button->IsHover(input, context->GetAudio()))
	{
		button->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Exit));

		if (input->GetMouseData().left_button_state == MouseState::CLICKED)
		{
			back = true;
		}
	}
	else
	{
		button->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Exit_Pressed));
	}
}

void Options::InitSliders()
{
	gef::Platform* platform = context->GetPlatform();
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();


	// Create volume sliders.
	float x_centre = platform->width() / 2.0f;
	float y_positions[] =
	{
		((platform->height() / 2.0f) - (platform->height() / 4.0f)),
		(platform->height() / 2.0f),
		((platform->height() / 2.0f) + (platform->height() / 4.0f))
	};

	std::string tags[] =
	{
		"Master",
		"SFX",
		"Music"
	};

	for (int index = 0; index < 3; ++index)
	{
		Slider* slider = Slider::Create(tags[index], gef::Vector4(x_centre, y_positions[index], -0.1f));
		slider->set_height(32.0f);
		slider->set_width(32.0f);
		slider->set_position(slider->MaxPosition(), y_positions[index], 0.0f);
		slider->SetBarBackdrop(context->GFXData()->GetTexture(TextureID::Slider_Background));
		slider->SetBarVolumeTexture(context->GFXData()->GetTexture(TextureID::Slider_Foreground));
		sliders.push_back(slider);
	}


}

void Options::RenderFont()
{
	//Position data & Text information.
	float x_pos = 0.0f;
	float y_pos = 0.0f;
	const char* text[] =
	{
		"Master",
		"Sound Effects",
		"Music"
	};

	for (int index = 0; index <option_text.size(); ++index)
	{
		if (option_text.at(index) != nullptr)
		{
			//Calculate position with respect to volume bar.
			x_pos = sliders.at(index)->BackBarGraphics().position().x() + 64.0f;
			y_pos = sliders.at(index)->BackBarGraphics().position().y() - 64.0f;

			//Render the volume bar text.
			option_text.at(index)->RenderText
			(
				context->SpriteRenderer(),
				gef::Vector4(x_pos, y_pos, -0.1f),
				1.0f,
				0xffffffff,
				gef::TextJustification::TJ_LEFT,
				text[index]
			);
		}
	}
}

void Options::InitTileOptions()
{
	gef::Platform* platform = context->GetPlatform();
	tiles_font[0] = new gef::Font(*platform);
	tiles_font[0]->Load("comic_sans");
	tiles_font[1] = new gef::Font(*platform);
	tiles_font[1]->Load("comic_sans");

	float x_pos = context->GetPlatform()->width() / 2.0f;
	float y_pos = context->GetPlatform()->height() - 128.0f;
	int negate = -1;
	for (int index = 0; index < tile_option_arrows.size(); ++index) 
	{
		tile_option_arrows[index] = UIButton::Create("", gef::Vector4((x_pos + 64.0f) * negate, y_pos, -0.1f));
		tile_option_arrows[index]->set_texture(context->GFXData()->GetTexture(TextureID::));
		negate = 1;
	}
	
}

void Options::RenderTilesFont()
{
}
