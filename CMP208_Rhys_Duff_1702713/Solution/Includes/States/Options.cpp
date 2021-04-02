#include "pch.h"
#include "Options.h"
#include "Context.h"
#include "system/platform.h"

Options::Options(gef::Platform* platform)
{
	back = false;

	// Create volume sliders.
	
	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 4.0f))),
		((platform->height() / 2.0f)),
		((platform->height() / 2.0f) + ((platform->height() / 4.0f)))
	};

	for (int index = 0; index < 3; ++index)
	{
		Slider* slider = Slider::Create("", gef::Vector2(platform->width() / 2.0f, y_positions[index]));
		gef::ImageData slider_img_data;
		slider->set_height(32.0f);
		slider->set_width(32.0f);

		sliders.push_back(slider);
	}
}

Options::~Options()
{
	for (auto slider : sliders)
	{
		delete slider;
		slider = nullptr;
	}

	sliders.clear();
	sliders.resize(0);
}

void Options::OnEnter()
{
	gef::Platform* platform = context->GetPlatform();

	float centre_x = ((context->GetPlatform()->width() / 2.0f));


	// Create back button.
	button = UIButton::Create("Back", gef::Vector2(100.0f,
		context->GetPlatform()->height() - context->GetPlatform()->height() / 8.0f)
	);

	gef::ImageData image_data;
	context->GetAssetLoader()->png_loader.Load("buttons/exit-pressed.png", *context->GetPlatform(), image_data);
	gef::Texture* back_button_tex = gef::Texture::Create(*context->GetPlatform(), image_data);
	button->set_height(50.0f);
	button->set_width(100.0f);
	button->set_texture(back_button_tex);

}

void Options::Input(float delta_time)
{
	PawnController* input = context->GetInput();

	input->GetInputManager()->Update();
	input->ProcessTouchInput();

	if (button->IsHover(input) && input->GetMouseData().left_button_state == MouseState::CLICKED)
	{
		back = true;
	}


	for (auto& slider : sliders)
	{
		if (slider->IsHover(input) && input->GetMouseData().left_button_state == MouseState::IS_DOWN)
		{
			slider->UpdatePosition(input->GetMouseData());
		}
	}
	

}

bool Options::Update(float delta_time)
{

	for (auto& slider : sliders)
	{
		slider->Update(delta_time);
	}
	
	button->Update(delta_time);

	if (back)
	{
		context->Transition(States::MAIN);
	}

	return true;
}

void Options::Render()
{
	gef::SpriteRenderer* sprite_renderer = this->context->SpriteRenderer();

	sprite_renderer->Begin(true);


	for (auto& slider : sliders)
	{
		slider->Render(sprite_renderer);
	}

		button->Render(sprite_renderer);
		

	sprite_renderer->End();

}

void Options::OnExit()
{
	delete button;
	button = false;

	back = false;
}
