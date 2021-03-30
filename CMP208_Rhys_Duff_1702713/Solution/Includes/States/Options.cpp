#include "pch.h"
#include "Options.h"
#include "Context.h"
#include "system/platform.h"

Options::Options()
{


}

Options::~Options()
{
}

void Options::OnEnter()
{
	float centre_x = ((context->GetPlatform()->width() / 2.0f));


	std::string tags[] = { "Continue",  "Back" };
	float y_positions[] =
	{
		((context->GetPlatform()->height() / 2.0f) - ((context->GetPlatform()->height() / 4.0f))),
		((context->GetPlatform()->height() / 2.0f) + ((context->GetPlatform()->height() / 4.0f)))
	};

	for (uint32 index = 0; index < 2; ++index)
	{
		UIButton* button = UIButton::Create(tags[index], gef::Vector2(centre_x, y_positions[index]));
		this->context->GetAssetLoader()->png_loader.Load("ButtonTest.png", *platform, image);								//Fill image data with a loaded png.

		gef::Texture* texture = gef::Texture::Create(*platform, image);														//Create a texture using the populated image data.
		button->set_texture(texture);
		button->InitFont(context->GetPlatform());
		buttons.push_back(button);
	}

	Slider* slider = Slider::Create("Volume", gef::Vector2(100.0f, 100.0f));

	

}

void Options::Input(float delta_time)
{
	//Evaluate input for each button.
	for (auto& button : buttons)
	{
		button->EvaluateButtonState(this->context->GetInput());
	}
}

bool Options::Update(float delta_time)
{
	for (auto& button : buttons)
	{
		button->Update(delta_time);
	}

	return false;
}

void Options::Render()
{
	gef::SpriteRenderer* sprite_renderer = this->context->SpriteRenderer();

	sprite_renderer->Begin(false);

	for (auto& button : buttons)
	{
		button->Render(sprite_renderer);
	}

	sprite_renderer->End();

}

void Options::OnExit()
{
}
