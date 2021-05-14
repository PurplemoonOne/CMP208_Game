#include "pch.h"
#include "PauseMenu.h"

#include "Context.h"

#include <system/platform.h>
#include <Input/sony_controller_input_manager.h>

#include "Utilities/AssetLoader.h"



PauseMenu::PauseMenu(gef::Platform* platform_)
	:
	backdrop(nullptr),
	session_clock(0.0f),
	button_pressed(false),
	index(0)
{
	std::fill(buttons.begin(), buttons.end(), nullptr);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::OnEnter()
{
	LoadButtons();
	LoadBackdrop();
}

void PauseMenu::Input(float delta_time)
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
					buttons[index]->IsSelected(false);
					index = (index == (buttons.size() - 1)) ? 0 : index + 1;
				}
				else if (controller->buttons_pressed() == gef_SONY_CTRL_UP)
				{
					buttons[index]->IsSelected(false);
					index = (index == 0) ? (buttons.size() - 1) : index - 1;
				}

				buttons[index]->IsSelected(true);


				if (controller->buttons_pressed() == gef_SONY_CTRL_CROSS)
				{
					button_pressed = true;
				}
				else
				{
					button_pressed = false;
				}
			}
		}
	}
	else
	{
		IsMouseHoveringOverButton();
	}
}

bool PauseMenu::Update(float delta_time)
{
	session_clock += 1.0f * delta_time;

	backdrop->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, (context->GetPlatform()->height() / 2.0f) - 256.0f, 0.2f));

	for (auto& button : buttons)
	{
		button->Update(delta_time);
	}

	UpdateTransition();
	UpdateButtonTextures();

	return true;
}

void PauseMenu::Render()
{

	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	sprite_renderer->Begin(true);

		sprite_renderer->DrawSprite(*backdrop);

		for (UIButton* button : buttons)
		{
			button->Render(sprite_renderer);
		}

	sprite_renderer->End();
}

void PauseMenu::OnExit()
{
	session_clock = 0.0f;


	for (auto& button : buttons)
	{
		delete button;
	}

	if (backdrop)
	{
		delete backdrop;
		backdrop = nullptr;
	}

}

void PauseMenu::IsMouseHoveringOverButton()
{
	PawnController* input = this->context->GetInput();

	for (int index = 0; index < buttons.size(); ++index)
	{
		if (buttons[index]->IsHover(input, context->GetAudio()))
		{
			buttons[index]->IsSelected(true);
		}
		else
		{
			buttons[index]->IsSelected(false);
		}
	}
}

void PauseMenu::UpdateTransition()
{

	if (buttons[0]->CurrentlySelected())
	{
		if ((context->GetInput()->GetMouseData().left_button_state == MouseState::CLICKED) || button_pressed)
		{
			context->SetGameIsRunning(true);
			context->Transition(States::GAME);
		}
	}
	else if (buttons[1]->CurrentlySelected())
	{
		if ((context->GetInput()->GetMouseData().left_button_state == MouseState::CLICKED) || button_pressed)
		{
			context->Transition(States::OPTIONS);
		}
	}
	else if (buttons[2]->CurrentlySelected())
	{
		if ((context->GetInput()->GetMouseData().left_button_state == MouseState::CLICKED) || button_pressed)
		{
			context->Transition(States::MAIN);
		}
	}
}

void PauseMenu::UpdateButtonTextures()
{
	if (buttons[0]->CurrentlySelected())
	{
		buttons[0]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Play_Pressed));
	}
	else
	{
		buttons[0]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Play));
	}

	if (buttons[1]->CurrentlySelected())
	{
		buttons[1]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Options_Pressed));
	}
	else
	{
		buttons[1]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Options));
	}

	if (buttons[2]->CurrentlySelected())
	{
		buttons[2]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Exit_Pressed));
	}
	else
	{
		buttons[2]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Exit));
	}
}


void PauseMenu::LoadBackdrop()
{
	gef::Platform* platform = context->GetPlatform();
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();

	//Initialise backdrop.
	backdrop = new gef::Sprite();
	backdrop->set_texture(context->GFXData()->GetTexture(TextureID::forest_background));
	backdrop->set_height(platform->height() + 512);
	backdrop->set_width(platform->width());
	backdrop->set_position(gef::Vector4(platform->width() / 2.0f, (platform->height() / 2.0f) + 256.0f, 0.2f));
}

void PauseMenu::LoadButtons()
{
	gef::Platform* platform = context->GetPlatform();
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();

	/*..Create our buttons..*/
	float centre_x = ((platform->width() / 4.0f));

	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 4.0f))),
		((platform->height() / 2.0f)),
		((platform->height() / 2.0f) + ((platform->height() / 4.0f)))
	};

	for (uint32 index = 0; index < buttons.size(); ++index)
	{
		UIButton* button = UIButton::Create("", gef::Vector4(centre_x, y_positions[index], 0.1f));
		button->set_texture(context->GFXData()->GetButtonTexture((ButtonTextureID)index));
		button->InitFont(platform);
		button->set_height(50.0f);
		button->set_width(100.0f);
		button->CalculateAnchors();
		buttons[index] = button;
	}
}
