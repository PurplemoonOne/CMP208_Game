#include "pch.h"
#include "Slider.h"

#include "Input/PawnController.h"

Slider::Slider(std::string text, gef::Vector4 position, float depth)
	:
	UIButton(text, position, depth)
{
	font = nullptr;
	
	//Set the backdrop bar as a visual assist.
	bar_backdrop.set_position(gef::Vector4(position.x(), position.y(), 0.1f));
	bar_volume.set_position(gef::Vector4(position.x(), position.y(), 0.1f));

	//Bar backdrop width and height.
	bar_backdrop.set_width(640.0f);
	bar_backdrop.set_height(10.0f);
	//Bar volumes width and height.
	bar_volume.set_width(10.0f);
	bar_volume.set_height(10.0f);

	min_value = position_.x() - (bar_backdrop.width() / 2.0f);
	max_value = position_.x() + (bar_backdrop.width() / 2.0f);

	//Work out the volume values from 0 to X. Where X is the max volume.
	min_volume = min_value - min_value;
	max_volume = max_value - min_value;
}

Slider* Slider::Create( std::string text, gef::Vector4 position, float depth)
{
	return new Slider(text, position, depth);
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
//	bar_volume.set_width();

	if (position_.x() > max_value)
		set_position(max_value, position_.y(), 0.0f);

	if (position_.x() < min_value)
		set_position(min_value, position_.y(), 0.0f);
}

void Slider::SetBarBackdrop(const gef::Texture* texture)
{
	bar_backdrop.set_texture(texture);
}

void Slider::SetBarVolumeTexture(const gef::Texture* texture)
{
	bar_volume.set_texture(texture);
}

void Slider::Render(gef::SpriteRenderer* sprite_renderer)
{
	sprite_renderer->DrawSprite(bar_backdrop);
	sprite_renderer->DrawSprite(bar_volume);
	sprite_renderer->DrawSprite(*this);
}

void Slider::UpdateVolumeBar()
{
}

