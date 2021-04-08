#include "pch.h"
#include "DeathScreen.h"

/*..input..*/
#include "Input/PawnController.h"

/*..Context..*/
#include "Context.h"

/*..platform..*/
#include "system/platform.h"

/*..buttons..*/
#include "UserInterface/UIButton.h"

/*..SCE..*/
#include <Input/sony_controller_input_manager.h>

DeathScreen::DeathScreen(gef::Platform* platform_)
{
	game_state = false;
	exit = false;
	session_clock = 0.0f;
}

DeathScreen::~DeathScreen()
{

}

void DeathScreen::OnEnter()
{
	gef::Platform* platform = context->GetPlatform();


	/*..Create tags, titles and prefixes to make appending easier..*/
	std::string tags[] = { "Play", "Exit" };
	std::string prefix = "buttons/";
	std::string suffix = ".png";
	std::string filenames[] =
	{
		"play-pressed",
		"playYellow",
		"exit-pressed",
		"exitYellow"
	};


	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 3.0f))),
		((platform->height() / 2.0f) + ((platform->height() / 3.0f)))
	};

	float centre_x = ((platform->width() / 2.0f));
	float depth = 0.1f;
	int index = 0;

	for (int i = 0; i < buttons.size(); ++i)
	{
		i == 2 ? index++ : 0;

		UIButton* button = UIButton::Create("", gef::Vector4(centre_x, y_positions[index], 0.1f), 0.1f);

		//Append filepath.
		std::string final_path = prefix + filenames[i] + suffix;

		//Convert to C style string.
		//Fill image data with a loaded png.
		context->GFXData()->GetAssetLoader()->png_loader.Load(final_path.c_str(), *platform, image);

		//Create a texture using the populated image data.
		gef::Texture* texture = gef::Texture::Create(*platform, image);

		button->set_texture(texture);
		button->InitFont(platform);
		button->set_height(50.0f);
		button->set_width(100.0f);
		buttons[i] = button;
		//Clear last filepath.
		final_path.clear();
	}

}

void DeathScreen::Input(float delta_time)
{
	PawnController* input = this->context->GetInput();

	input->GetInputManager()->Update(); //Update the input.
	input->ProcessTouchInput();

	// Simple input processing : check which state we wish to enter.
	const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();

	if (sce_manger)
	{
		const gef::SonyController* controller = sce_manger->GetController(0);

		if (controller)
		{
			if (controller->buttons_down() == gef_SONY_CTRL_CROSS || buttons[0]->IsHover(input) &&
				input->GetMouseData().left_button_state == MouseState::CLICKED)
			{
				game_state = true;
			}
	
			if (controller->buttons_down() == gef_SONY_CTRL_TRIANGLE || buttons[2]->IsHover(input) &&
				input->GetMouseData().left_button_state == MouseState::CLICKED)
			{
				exit = true;
			}
		}
	}
}

bool DeathScreen::Update(float delta_time)
{
	session_clock += 1.0f * delta_time;
	for (auto& button : buttons)
	{
		button->Update(delta_time);
	}


	if (game_state) {
		context->SetGameIsRunning(true);
		context->Reset(true);
		context->Transition(States::GAME);
	}
	else if (exit) {
		context->SetGameIsRunning(false);
		context->Transition(States::MAIN);
	}

	return true;
}

void DeathScreen::Render()
{
	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	sprite_renderer->Begin(true);


	for (UIButton* button : buttons)
	{
		button->Render(sprite_renderer);
	}

	sprite_renderer->End();
}

void DeathScreen::OnExit()
{
	for (auto& button : buttons)
	{
		if (button)
		{
			if (button->texture())
			{
				delete button->texture();
				button->set_texture(nullptr);
			}

			delete button;
			button = nullptr;
		}
	}

	game_state = false;
	exit = false;
}
