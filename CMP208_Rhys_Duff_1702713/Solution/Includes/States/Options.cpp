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
	tile_option_arrows.fill(nullptr);
	tiles_to_render = 4;
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
	InitTileOptions();

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
				if (controller->buttons_pressed() == gef_SONY_CTRL_DOWN)
				{
					if (sliders[index])
					{
						sliders[index]->IsSelected(false);
						index = (index == (sliders.size() - 1)) ? 0 : index + 1;
					}
				}
				else if (controller->buttons_pressed() == gef_SONY_CTRL_UP)
				{
					if (sliders[index])
					{
						sliders[index]->IsSelected(false);
						index = (index == 0) ? (sliders.size() - 1) : index - 1;
					}
				}

				if (sliders[index])
				{
					sliders[index]->IsSelected(true);
					tile_arrows_selected = false;
				}
				else
				{
					tile_arrows_selected = true;
				}
			

				if (controller->buttons_pressed() == gef_SONY_CTRL_RIGHT)
				{
					if(sliders[index])
					sliders[index]->UpdatePosition(input->GetMouseData(), 20.0f);
				}
				else if (controller->buttons_pressed() == gef_SONY_CTRL_LEFT)
				{
					if(sliders[index])
					sliders[index]->UpdatePosition(input->GetMouseData(), -20.0f);
				}

			}
		}
	}
	else
	{
		for (auto& slider : sliders)
		{
			if(slider)
			if (slider->IsHover(input, context->GetAudio()) && input->GetMouseData().left_button_state == MouseState::IS_DOWN)
			{
				slider->UpdatePosition(input->GetMouseData(), 0.0f);
			}
		}
	}

	EvalButton();
	EvalArrowButtons(0);
	EvalArrowButtons(1);
}

bool Options::Update(float delta_time)
{
	UpdateVolume();
	for (auto& slider : sliders)
	{
		if(slider)
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
		RenderTilesFont();
		
		for (auto& slider : sliders)
		{
			if(slider)
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

	for (auto& arrow : tile_option_arrows)
	{
		if (arrow)
		{
			delete arrow;
			arrow = nullptr;
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

	sliders.push_back(nullptr);

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
	int negate = 1;

	TextureID ids[] = 
	{
		TextureID::right_arrow,
		TextureID::left_arrow, 
	};

	for (int index = 0; index < tile_option_arrows.size(); ++index) 
	{
		tile_option_arrows[index] = UIButton::Create("", gef::Vector4((x_pos + 128.0f) * negate, y_pos, -0.1f));
		tile_option_arrows[index]->set_texture(context->GFXData()->GetTexture(ids[index]));
		tile_option_arrows[index]->set_height(64.0f);
		tile_option_arrows[index]->set_width(64.0f);

		index == 0 ? negate = -1 : negate = 1;	//Flip the arrow position.
	}
	
}

void Options::EvalArrowButtons(const int index)
{
	PawnController* input = context->GetInput();

	float x_pos = context->GetPlatform()->width() / 2.0f;
	float y_pos = context->GetPlatform()->height() - 128.0f;

	int negate = 1;

	if (input)
	{

		if (tile_option_arrows[index])
		{
			//
			index == 0 ? negate = 1 : negate = -1;
			tile_option_arrows[index]->set_position(gef::Vector4(x_pos + 128.0f * negate, y_pos, -0.1f));

			if (tile_option_arrows[index]->IsHover(input, context->GetAudio()))//Don't need audio.
			{
				UpdateDpadTextures(index);
				//Evaluate if the mouse has been clicked.
				if (input->GetMouseData().left_button_state == MouseState::CLICKED)
				{
					IncrimentTiles(index);
				}
			}
			else
			{
					UpdateDpadTextures(index);
			}
		}
	}


	//Handle controller input.
	if (tile_arrows_selected)
	{
		const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();

		if (sce_manger)
		{
			const gef::SonyController* controller = sce_manger->GetController(0);

			if (controller)
			{
				if (controller->buttons_pressed() == gef_SONY_CTRL_LEFT)
				{
					IncrimentTiles(1);
					UpdateDpadTextures(1);
				}
				if (controller->buttons_pressed() == gef_SONY_CTRL_RIGHT)
				{
					IncrimentTiles(0);
					UpdateDpadTextures(0);
				}
			}
		}
	}
}


void Options::RenderTilesFont()
{
	gef::SpriteRenderer* sp = context->SpriteRenderer();

	float x_pos = context->GetPlatform()->width() / 2.0f;
	float y_pos = context->GetPlatform()->height() - 128.0f;

	//Display number of tiles.
	tiles_font[0]->RenderText
	(
		sp,
		gef::Vector4(x_pos, y_pos, -0.1f),
		1.0f,
		0xFFFFFFFF,
		gef::TextJustification::TJ_LEFT,
		"%i",
		tiles_to_render
	);

	//Render title.
	tiles_font[1]->RenderText
	(
		sp,
		gef::Vector4(x_pos, y_pos - 64.0f, -0.1f),
		1.0f,
		0xFFFFFFFF,
		gef::TextJustification::TJ_LEFT,
		"Tiles to render :"
	);

	for (auto& arrow : tile_option_arrows)
	{
		if (arrow)
		{
			sp->DrawSprite(*arrow);
		}
	}
}

void Options::IncrimentTiles(const int& index)
{
	if(index == 0)
	{
		tiles_to_render++;
		tiles_to_render > 8 ? tiles_to_render = 2 : NULL;
	}
	else
	{
		tiles_to_render--;
		tiles_to_render < 2 ? tiles_to_render = 8 : NULL;
	}
}

void Options::UpdateDpadTextures(const int& index)
{
	//Display the correct texture.
	index == 0 ?

		tile_option_arrows[index]->set_texture(context->GFXData()->GetTexture(TextureID::right_arrow_pressed))
		:
		tile_option_arrows[index]->set_texture(context->GFXData()->GetTexture(TextureID::left_arrow_pressed));
}
