#include "pch.h"
#include "PauseMenu.h"

#include "Context.h"

#include <system/platform.h>
#include <Input/sony_controller_input_manager.h>

#include "Utilities/AssetLoader.h"



PauseMenu::PauseMenu(gef::Platform* platform_)
{
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

	uint32 tag_index = 0;//Need a seperate counter for our tags.

	for (uint32 index = 0; index < 6; ++index)
	{
		//Incriment our tag index.
		index == 2 || index == 4 ? tag_index++ : 0;

		UIButton* button = UIButton::Create("", gef::Vector4(centre_x, y_positions[tag_index], 0.1f), 0.1f);

		button->set_texture(context->GFXData()->GetTexture((TextureID)index));
		button->InitFont(platform);
		button->set_height(50.0f);
		button->set_width(100.0f);
		button->CalculateAnchors();
		buttons[index] = button;
	}
}

void PauseMenu::Input(float delta_time)
{
	PawnController* input = this->context->GetInput();

	input->GetInputManager()->Update();
	input->ProcessTouchInput();

	// Simple input processing : check which state we wish to enter.
	const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();

	if (sce_manger)
	{
		const gef::SonyController* controller = sce_manger->GetController(0);

		if (controller)
		{
			if (controller->buttons_down() == gef_SONY_CTRL_CROSS || buttons[0]->IsHover(input) &&
				input->GetMouseData().left_button_state == MouseState::CLICKED ||
				input->GetInputManager()->keyboard()->IsKeyPressed(gef::Keyboard::KeyCode::KC_ESCAPE))
			{
				game_state = true;
			}
			if (controller->buttons_down() == gef_SONY_CTRL_CIRCLE || buttons[2]->IsHover(input) &&
				input->GetMouseData().left_button_state == MouseState::CLICKED)
			{
				options = true;
			}
			if (controller->buttons_down() == gef_SONY_CTRL_TRIANGLE || buttons[4]->IsHover(input) &&
				input->GetMouseData().left_button_state == MouseState::CLICKED)
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


	// Handle transitioning between states.
	if (game_state) 
	{
		context->Transition(States::GAME);
	}
	if (options)
	{
		context->Transition(States::OPTIONS);
	}
	else if (exit) {
		context->SetGameIsRunning(false);
		context->Transition(States::MAIN);
	}

	return true;
}

void PauseMenu::Render()
{

	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	sprite_renderer->Begin(true);

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
	options = false;
	session_clock = 0.0f;


	for (auto& button : buttons)
	{
		delete button;
	}

}
