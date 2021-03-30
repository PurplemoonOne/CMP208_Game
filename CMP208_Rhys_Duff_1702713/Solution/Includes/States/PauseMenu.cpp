#include "pch.h"
#include "PauseMenu.h"

#include "Context.h"

#include <system/platform.h>
#include <Input/sony_controller_input_manager.h>

#include "Utilities/AssetLoader.h"



PauseMenu::PauseMenu(gef::Platform* platform_)
{
	platform = platform_;

	game_state = false;
	options = false;
	exit = false;

	session_clock = 0.0f;

}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::OnEnter()
{
	float centre_x = ((context->GetPlatform()->width() / 2.0f));

	std::string tags[] = { "Continue", "Options", "Exit to Desktop" };
	float y_positions[] =
	{
		((context->GetPlatform()->height() / 2.0f) - ((context->GetPlatform()->height() / 4.0f))),
		((context->GetPlatform()->height() / 2.0f)),
		((context->GetPlatform()->height() / 2.0f) + ((context->GetPlatform()->height() / 4.0f)))
	};

	for (uint32 index = 0; index < 3; ++index)
	{
		UIButton* button = UIButton::Create(tags[index], gef::Vector2(centre_x, y_positions[index]));
		context->GetAssetLoader()->png_loader.Load("ButtonTest.png", *platform, image);		//Fill image data with a loaded png.

		gef::Texture* texture = gef::Texture::Create(*platform, image);								//Create a texture using the populated image data.
		button->set_texture(texture);
		button->InitFont(context->GetPlatform());
		buttons.push_back(button);
	}
}

void PauseMenu::Input(float delta_time)
{
	PawnController* input = this->context->GetInput();
		
				input->GetInputManager()->Update(); //Update the input.
	
				// Simple input processing : check which state we wish to enter.
				const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();
	
				if (sce_manger)
				{
					const gef::SonyController* controller = sce_manger->GetController(0);
	
						if (controller)
						{
								if (input->GetInputManager()->keyboard()->IsKeyPressed(gef::Keyboard::KeyCode::KC_ESCAPE)
									|| buttons[0]->EvaluateButtonState(input) == ButtonState::CLICKED)
								{
									game_state = true;
								}
								if (controller->buttons_down() == gef_SONY_CTRL_TRIANGLE || buttons[2]->EvaluateButtonState(input) == ButtonState::CLICKED)
								{
									exit = true;
								}
						}
				}
		
}

bool PauseMenu::Update(float delta_time)
{
	session_clock += 1.0f * delta_time;


	for (auto& button : buttons)
	{
		button->Update(delta_time);
	}

	if (game_state) {
		context->Transition(States::GAME);
	}
	else if (exit) {
		return false;
	}
}

void PauseMenu::Render()
{
	gef::SpriteRenderer* sprite_renderer = this->context->SpriteRenderer();

	sprite_renderer->Begin(false);

		for (UIButton* button : buttons)
		{
			button->Render(sprite_renderer);
		}

	sprite_renderer->End();
}

void PauseMenu::OnExit()
{
	game_state = false;
	exit = false;
	session_clock = 0.0f;


	for (auto& button : buttons)
	{
		delete button;
	}

	buttons.clear();
	buttons.resize(0);
}
