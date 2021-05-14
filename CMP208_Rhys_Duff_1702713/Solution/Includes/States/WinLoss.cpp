#include "pch.h"
#include "WinLoss.h"

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

WinLoseScreen::WinLoseScreen(gef::Platform* platform_)
	:
	game_state(false),
	exit(false),
	final_score_text(nullptr),
	session_clock(0.0f)
{
	//Fill both arrays with nullptr values.
	buttons.fill(nullptr);
	sprites.fill(nullptr);
	
}

WinLoseScreen::~WinLoseScreen()
{

}

void WinLoseScreen::OnEnter()
{
	gef::Platform* platform = context->GetPlatform();

	/*..Attributes..*/
	//Work out positions for the buttons based on window size.
	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 3.0f))),
		((platform->height() / 2.0f) + ((platform->height() / 3.0f)))
	};

	float centre_x = ((platform->width() / 2.0f));
	float depth = 0.1f;
	int index = 0;

	//Create new buttons.
	for (int i = 0; i < buttons.size(); ++i)
	{
		i == 1 ? index = 4 : NULL;//Need exit sprite.

		UIButton* button = UIButton::Create("", gef::Vector4(centre_x, y_positions[i], 0.1f));
		button->set_texture(context->GFXData()->GetTexture((TextureID)index));
		button->InitFont(platform);
		button->set_height(50.0f);
		button->set_width(100.0f);
		buttons[i] = button;
	}

	final_score_text = new gef::Font(*context->GetPlatform());
	final_score_text->Load("comic_sans");

	LoadBackdrop();
}

void WinLoseScreen::Input(float delta_time)
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
			if (controller->buttons_down() == gef_SONY_CTRL_CROSS)
			{
				game_state = true;
			}

			if (controller->buttons_down() == gef_SONY_CTRL_TRIANGLE)
			{
				exit = true;
			}
		}
	}
	EvalButtons();
}

bool WinLoseScreen::Update(float delta_time)
{
	session_clock += 1.0f * delta_time;
	UpdateSprites();//Update the background and death title.

	for (auto& button : buttons)
	{
		button->Update(delta_time);
	}

	UpdateDisplay(delta_time);

	return true;
}

void WinLoseScreen::Render()
{
	gef::SpriteRenderer* sprite_renderer = context->SpriteRenderer();

	sprite_renderer->Begin(true);

		//Render buttons, images and any other sprites necessary.
	    RenderText();

		RenderSprites(sprite_renderer);

		RenderButtons(sprite_renderer);

	sprite_renderer->End();
}

void WinLoseScreen::OnExit()
{
	//Delete all buttons and reset their values to null.
	for (auto& button : buttons)
	{
		if (button)
		{
			delete button;
			button = nullptr;
		}
	}

	//Delete all sprites and reset their values to null.
	for (auto& sprite : sprites)
	{
		if (sprite)
		{
			delete sprite;
			sprite = nullptr;
		}
	}

	if (final_score_text != nullptr)
	{
		delete final_score_text;
		final_score_text = nullptr;
		final_score = 0;
	}

	game_state = false;
	exit = false;
}

void WinLoseScreen::UpdateDisplay(float delta_time)
{
	if (!context->HasWon())
	{
		if (game_state) {
			context->SetGameIsRunning(true);
			context->Reset(true);
			context->Transition(States::GAME);
		}
		else if (exit) {
			context->SetGameIsRunning(false);
			context->Transition(States::MAIN);
		}
	}
	else 
	{
		if (exit) {
		context->SetGameIsRunning(false);
		context->Transition(States::MAIN);
		}
	}

}

void WinLoseScreen::EvalButtons()
{
	PawnController* input = this->context->GetInput();

	if (buttons[0]->IsHover(input, context->GetAudio()))
	{
		buttons[0]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Play));

		if (input->GetMouseData().left_button_state == MouseState::CLICKED)
		{
			game_state = true;
		}
	}
	else
	{
		buttons[0]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Play_Pressed));
	}

	if (buttons[1]->IsHover(input, context->GetAudio()))
	{
		buttons[1]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Exit));

		if (input->GetMouseData().left_button_state == MouseState::CLICKED)
		{
			exit = true;
		}
	}
	else
	{
		buttons[1]->set_texture(context->GFXData()->GetButtonTexture(ButtonTextureID::Button_Exit_Pressed));
	}
}

void WinLoseScreen::RenderButtons(gef::SpriteRenderer* sprite_renderer)
{
	if (!context->HasWon())
	{
		for (UIButton* button : buttons)
		{
			button->Render(sprite_renderer);
		}
	}
	else
	{
		sprite_renderer->DrawSprite(*buttons[1]);
	}
}

void WinLoseScreen::LoadBackdrop()
{
	sprites[0] = new gef::Sprite();
	sprites[0]->set_texture(context->GFXData()->GetTexture(TextureID::death_screen));
	sprites[0]->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, context->GetPlatform()->height() / 2.0f, 0.2f));
	sprites[0]->set_width(context->GetPlatform()->width());
	sprites[0]->set_height(context->GetPlatform()->height());

	sprites[1] = new gef::Sprite();
	sprites[1]->set_texture(context->GFXData()->GetTexture(TextureID::death_title));
	sprites[1]->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, context->GetPlatform()->height() / 2.0f, 0.2f));
	sprites[1]->set_width(512.0f);
	sprites[1]->set_height(512.0f);

	sprites[2] = new gef::Sprite();
	sprites[2]->set_texture(context->GFXData()->GetTexture(TextureID::level_complete));
	sprites[2]->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, context->GetPlatform()->height() / 2.0f, 0.2f));
	sprites[2]->set_width(1024.0f);
	sprites[2]->set_height(512.0f);

}

void WinLoseScreen::UpdateSprites()
{
	//Update backdrop.
	sprites[0]->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, context->GetPlatform()->height() / 2.0f, 0.2f));
	sprites[0]->set_width(context->GetPlatform()->width());
	sprites[0]->set_height(context->GetPlatform()->height());
	sprites[1]->set_position(gef::Vector4(context->GetPlatform()->width() / 2.0f, context->GetPlatform()->height() / 2.0f, 0.2f));
	sprites[1]->set_width(512.0f);
	sprites[1]->set_height(512.0f);
}

void WinLoseScreen::RenderSprites(gef::SpriteRenderer* sprite_renderer)
{
	sprite_renderer->DrawSprite(*sprites[0]);

	if (!context->HasWon()) {
		sprite_renderer->DrawSprite(*sprites[1]);
	}
	else {
		sprite_renderer->DrawSprite(*sprites[2]);
	}
}

void WinLoseScreen::RenderText()
{
	float screen_pos_x = context->GetPlatform()->width() / 2.0f;
	float screen_pos_y = context->GetPlatform()->height() / 3.0f;

	final_score_text->RenderText
	(
		context->SpriteRenderer(),
		gef::Vector4(screen_pos_x, screen_pos_y, -0.1f),
		1.0f,
		0xFFFFFFFF,
		gef::TextJustification::TJ_LEFT,
		"Your score : %i",
		final_score
	);

}
