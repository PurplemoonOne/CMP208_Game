#include "pch.h"

/*..Essentials..*/
#include "MainMenu.h"
#include "UserInterface/UIButton.h"
#include "Context.h"

#include <Input/sony_controller_input_manager.h>
#include <system/platform.h>

MainMenu::MainMenu(gef::Platform* platform_)
	:
	title(nullptr),
	index(0),
	session_clock(0.0f),
	button_pressed(false),
	not_exit(true),
	parallax_bg(nullptr)
{
	buttons.fill(nullptr);

	float velocity = 4.0f;
}

MainMenu::~MainMenu()
{
	OnExit();
}

void MainMenu::OnEnter()
{
	// Check if we're playing any music.
	if (!context->GetAudio()->IsMusicPlaying(MusicID::MENU))
	{
		context->GetAudio()->PlayMusic(MusicID::MENU);
	}

	LoadBackdrop();
	LoadButtons();
}

void MainMenu::Input(float delta_time)
{
	PawnController* input = context->GetInput();

	input->GetInputManager()->Update(); //Update the input.
	input->ProcessTouchInput();

	// Simple input processing : check which state we wish to enter.
	const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();

	if(input->ControllerActive())
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

bool MainMenu::Update(float delta_time)
{
	session_clock += 1.0f * delta_time;

	// Update the button textures and update the state.
	UpdateButtonTextures();
	UpdateTransition();	
	AnimateTitle(delta_time);

	if(parallax_bg)
	parallax_bg->UpdateMenuVersion(delta_time);

	return not_exit;
}


void MainMenu::Render()
{
	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	sprite_renderer->Begin(true);

		//Draw background first.
		parallax_bg->Render(sprite_renderer);

		sprite_renderer->DrawSprite(*title);

		// Render Buttons.
		for (UIButton* button : buttons)
		{
			button->Render(sprite_renderer);
		}

	sprite_renderer->End();

}


void MainMenu::OnExit()
{
	//Clear some memory.
	session_clock = 0.0f;

	for (auto& button : buttons)
	{
		if (button)
		{
			delete button;
			button = nullptr;
		}
	}

	for (auto& button : buttons)
	{
		if (button)
		{
			delete button;
			button = nullptr;
		}
	}

	if (title)
	{
		delete title;
		title = nullptr;
	}

	if (parallax_bg)
	{
		delete parallax_bg;
		parallax_bg = nullptr;
	}

}

void MainMenu::LoadButtons()
{
	gef::Platform* platform = context->GetPlatform();


	/*..Create our buttons..*/
	float centre_x = (platform->width() / 4.0f);
	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 4.0f))),
		((platform->height() / 2.0f)),
		((platform->height() / 2.0f) + ((platform->height() / 4.0f)))
	};

	for (int32 index = 0; index < buttons.size(); ++index)
	{
		UIButton* button = UIButton::Create("", gef::Vector4(centre_x, y_positions[index], -0.2f));
		button->set_texture(context->GFXData()->GetButtonTexture((ButtonTextureID)index));	//Get the created texture and set the button accordingly.
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
	title = new gef::Sprite();
	title->set_texture(context->GFXData()->GetTexture(TextureID::ode));
	title->set_height(0.0f);
	title->set_width(0.0f);
	title->set_position(gef::Vector4(platform->width() / 2.0f, platform->height() / 3.0f, -0.1f));


	parallax_bg = ParallaxBackground::Create(platform, context->GFXData());
}

void MainMenu::IsMouseHoveringOverButton()
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

void MainMenu::UpdateTransition()
{

	if (buttons[0]->CurrentlySelected())
	{
		if ((context->GetInput()->GetMouseData().left_button_state == MouseState::CLICKED) || button_pressed)
		{
			context->SetGameIsRunning(true);
			context->Transition(States::GAME);
			//Stop Playing music.
			context->GetAudio()->PlayMusic(MusicID::null);
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
			not_exit = false;
		}
	}

}

void MainMenu::UpdateButtonTextures()
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

void MainMenu::AnimateTitle(float delta_time)
{
	//Animate the title 
	if (title)
	{
		title->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, context->GetPlatform()->height() / 3.0f, -0.1f));

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
}


