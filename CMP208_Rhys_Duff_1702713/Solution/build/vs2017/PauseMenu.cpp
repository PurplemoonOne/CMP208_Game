#include "pch.h"
#include "PauseMenu.h"

#include "Context.h"

#include <system/platform.h>

PauseMenu::PauseMenu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* pawn_controller_)
	:
	Menu(platform_, renderer_, sprite_renderer_, pawn_controller_)
{
	game_state = false;
	options = false;
	exit = false;

	session_clock = 0.0f;

	float centre_x = ((platform->width() / 2.0f));

	asset_loader = new AssetLoader(*platform);

	std::string tags[] = { "Continue", "Options", "Exit to Desktop" };
	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 4.0f))),
		((platform->height() / 2.0f)),
		((platform->height() / 2.0f) + ((platform->height() / 4.0f)))
	};

	for (uint32 index = 0; index < 3; ++index)
	{
		UIButton* button = UIButton::Create(platform, tags[index], gef::Vector2(centre_x, y_positions[index]));
			asset_loader->png_loader.Load("ButtonTest.png", *platform, image);								//Fill image data with a loaded png.

			gef::Texture* texture = gef::Texture::Create(*platform, image);				//Create a texture using the populated image data.
			button->set_texture(texture);

		buttons.push_back(button);
	}
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::OnEnter()
{

}

void PauseMenu::Input(float delta_time)
{

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

}
