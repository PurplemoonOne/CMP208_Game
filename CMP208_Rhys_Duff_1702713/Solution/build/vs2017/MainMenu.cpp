#include "pch.h"

/*..Essentials..*/
#include "MainMenu.h"
#include "UIButton.h"
#include "Context.h"

MainMenu::MainMenu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* input_):
Menu(platform_, renderer_, sprite_renderer_, input_)
{
	game_state = false;
	options = false;
	exit = false;

	session_clock = 0.0f;

	float centre_x = ((platform->width() / 2.0f));

	asset_loader = new AssetLoader(*platform);

	std::string tags[] = { "Play", "Options", "Exit" };
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

MainMenu::~MainMenu()
{
}

void MainMenu::OnEnter()
{

}

void MainMenu::Input(float delta_time)
{
	session_clock += 1.0f * delta_time;

	input->GetInputManager()->Update(); //Update the input.

	// Simple input processing : check which state we wish to enter.
	const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();

	if (sce_manger)
	{
		const gef::SonyController* controller = sce_manger->GetController(0);

		if (controller)
		{
			if (controller->buttons_down() == gef_SONY_CTRL_CROSS || buttons[0]->EvaluateButtonState(input) == ButtonState::CLICKED)
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


bool MainMenu::Update(float delta_time)
{

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


	return true;
}


void MainMenu::Render()
{

	sprite_renderer->Begin(true);


	for (UIButton* button : buttons)
	{
		button->Render(sprite_renderer);
	}

	sprite_renderer->End();

}


void MainMenu::OnExit()
{

	session_clock = 0.0f;


	buttons.clear();
	buttons.resize(0);

}
