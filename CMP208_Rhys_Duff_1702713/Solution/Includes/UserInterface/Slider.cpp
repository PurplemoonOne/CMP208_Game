#include "pch.h"
#include "Slider.h"

#include "Input/PawnController.h"

Slider::Slider(std::string text, gef::Vector2 position)
	:
	UIButton(text, position)
{
	font = nullptr;
	
	bar_backdrop.set_position(gef::Vector4(position.x, position.y, 0.0f));
	bar_backdrop.set_colour(0xffffffff);
	bar_backdrop.set_width(640.0f);
	bar_backdrop.set_height(10.0f);
	min_value = position_.x() - (bar_backdrop.width() / 2.0f);
	max_value = position_.x() + (bar_backdrop.width() / 2.0f);

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
}

void Slider::UpdatePosition(const MouseData& mouse_data)
{
	set_position(gef::Vector4(mouse_data.coordinates.x, position_.y(), 0.0f));

	if (position_.x() > max_value)
		set_position(max_value, position_.y(), 0.0f);

	if (position_.x() < min_value)
		set_position(min_value, position_.y(), 0.0f);
}

void Slider::SetBarBackdrop(const gef::Texture* texture)
{
	bar_backdrop.set_texture(texture);
}

void Slider::Render(gef::SpriteRenderer* sprite_renderer)
{
	sprite_renderer->Begin(true);

	sprite_renderer->DrawSprite(bar_backdrop);

	sprite_renderer->DrawSprite(*this);

	sprite_renderer->End();
}

