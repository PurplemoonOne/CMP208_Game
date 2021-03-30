#include "pch.h"
#include "Slider.h"

#include "Input/PawnController.h"

Slider::Slider(std::string text, gef::Vector2 position)
	:
	UIButton(text, position)
{
	position_ = gef::Vector4(position.x + 50.f, position.y, 0.0f);
	
	
	bar_backdrop.set_position(gef::Vector4(position.x, position.y, 0.0f));
	bar_backdrop.set_width(100.0f);
	bar_backdrop.set_height(25.0f);

	min_value = position_.x() - (width() / 2.0f);
	max_value = position_.x() + (width() / 2.0f);
}

Slider* Slider::Create( std::string text, gef::Vector2 position)
{
	return new Slider(text, position);
}

Slider::~Slider()
{
}

void Slider::Update(float delta_time)
{
	CalculateAnchors();

	if (button_state == ButtonState::CLICKED)
	{
		set_position(gef::Vector4(mouse_data->coordinates->x, mouse_data->coordinates->y, 0.0f));
		if (position_.x() > max_value)
			set_position(max_value, position_.y(), 0.0f);

		if (position_.x() < min_value)
			set_position(min_value, position_.y(), 0.0f);
	}


}

void Slider::SetBarBackdrop(const gef::Texture* texture)
{
	bar_backdrop.set_texture(texture);
}
