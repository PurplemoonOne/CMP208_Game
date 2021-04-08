#include "pch.h"

/*..Essentials..*/
#include "MainMenu.h"
#include "UserInterface/UIButton.h"
#include "Context.h"

#include <Input/sony_controller_input_manager.h>
#include <system/platform.h>

MainMenu::MainMenu(gef::Platform* platform_)
	:
	backdrop(nullptr),
	title(nullptr),
	game_state(false),
	options(false),
	exit(false),
	session_clock(0.0f)
{
}

MainMenu::~MainMenu()
{
	//Remove the camera.
	if (camera)
	{
		delete camera;
		camera = nullptr;
	}

	if (backdrop)
	{
		delete backdrop;
		backdrop = nullptr;
	}
}

void MainMenu::OnEnter()
{
	LoadBackdrop();
	LoadButtons();
	SetupCamera();
}

void MainMenu::Input(float delta_time)
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



bool MainMenu::Update(float delta_time)
{
	session_clock += 1.0f * delta_time;
	camera->Update(delta_time);

	for (auto& button : buttons)
	{
		button->Update(delta_time);
	}

	//Update the backdrop.
	backdrop->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, (context->GetPlatform()->height() / 2.0f) - 256.0f, 0.2f));
	title->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, context->GetPlatform()->height() / 3.0f, 0.1f));

	AnimateTitle(delta_time);

	if (game_state) {
		context->SetGameIsRunning(true);
		context->Transition(States::GAME);
	}
	else if (options)
	{
		context->Transition(States::OPTIONS);
	}
	else if (exit) {
		return false;
	}


	return true;
}


void MainMenu::Render()
{
	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	sprite_renderer->Begin(true);

		for (UIButton* button : buttons)
		{
			button->Render(sprite_renderer);
		}
	
		//Draw background first.
		sprite_renderer->DrawSprite(*backdrop);
		sprite_renderer->DrawSprite(*title);

	sprite_renderer->End();

}


void MainMenu::OnExit()
{
	//Clear some memory.
	session_clock = 0.0f;

	options = false;
	game_state = false;
	exit = false;

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

	//Remove camera.
	if (camera)
	{
		delete camera;
		camera = nullptr;
	}

	//Remove backdrop.
	if (backdrop)
	{
		if (backdrop->texture())
		{
			delete backdrop->texture();
			backdrop->set_texture(nullptr);
		}
		delete backdrop;
		backdrop = nullptr;
	}

	if (title)
	{
		if (title->texture())
		{
			delete title->texture();
			title->set_texture(nullptr);
		}
		delete title;
		title = nullptr;
	}
}

void MainMenu::LoadButtons()
{
	gef::Platform* platform = context->GetPlatform();
	/*..Create our buttons..*/
	float centre_x = ((platform->width() / 4.0f));

	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 4.0f))),
		((platform->height() / 2.0f)),
		((platform->height() / 2.0f) + ((platform->height() / 4.0f)))
	};

	uint32 tag_index = 0;
	for (int32 index = 0; index < buttons.size(); ++index)
	{
		index == 2 || index == 4 ? tag_index++ : NULL;
		UIButton* button = UIButton::Create("", gef::Vector4(centre_x, y_positions[tag_index], 0.1f), 0.1f);
		button->set_texture(context->GFXData()->GetTexture((TextureID)index));	//Get the created texture and set the button accordingly.
		button->InitFont(platform);
		button->set_height(50.0f);
		button->set_width(100.0f);
		buttons[index] = button;
	}

	
}

void MainMenu::LoadBackdrop()
{
	gef::Platform* platform = context->GetPlatform();
	AssetLoader* asset_loader = context->GFXData()->GetAssetLoader();

	//Initialise backdrop.
	backdrop = new gef::Sprite();
	backdrop->set_texture(asset_loader->Texture("forest_background/menu_backdrop.png", platform));
	backdrop->set_height(platform->height() + 512);
	backdrop->set_width(platform->width());
	backdrop->set_position(gef::Vector4(platform->width() / 2.0f, (platform->height() / 2.0f) + 256.0f, 0.2f));

	//Initialise backdrop.
	title = new gef::Sprite();
	title->set_texture(asset_loader->Texture("ode.png", platform));
	title->set_height(0.0f);
	title->set_width(0.0f);
	title->set_position(gef::Vector4(platform->width() / 2.0f, platform->height() / 3.0f, 0.1f));
}

void MainMenu::AnimateTitle(float delta_time)
{
	//Animate the title 
	if (title->width() <= 512.0f && title->height() <= 512.0f)
	{
		float width = title->width();
		float height = title->height();

		width += 128.0f * delta_time;
		height += 128.0f * delta_time;

		title->set_width(width);
		title->set_height(height);

	}
}


