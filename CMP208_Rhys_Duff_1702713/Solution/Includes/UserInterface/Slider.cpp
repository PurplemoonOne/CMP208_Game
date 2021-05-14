#include "pch.h"
#include "Slider.h"

#include "Input/PawnController.h"

Slider::Slider(std::string text, gef::Vector4 position)
	:
	UIButton(text, position)
{
	font = nullptr;
	
	//Set the backdrop bar as a visual assist.
	bar_backdrop.set_position(gef::Vector4(position.x(), position.y(), position.z()));
	bar_volume.set_position(gef::Vector4(position.x(), position.y(), position.z()));

	//Bar backdrop width and height.
	bar_backdrop.set_width(640.0f);
	bar_backdrop.set_height(32.0f);
	//Bar volumes width and height.
	bar_volume.set_width(640.0f);
	bar_volume.set_height(24.0f);

	min_value = position_.x() - (bar_backdrop.width() / 2.0f);
	max_value = position_.x() + (bar_backdrop.width() / 2.0f);

	//Work out the volume values from 0 to X. Where X is the max volume.
	min_volume = min_value - min_value;
	max_volume = max_value - min_value;

	CalculateBackBarAnchors();
}

Slider* Slider::Create( std::string text, gef::Vector4 position)
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

void Slider::UpdatePosition(const MouseData& mouse_data, float d_pad_input)
{
	//Set position of the button slider.
	if (d_pad_input != 0.0f) {
		set_position(gef::Vector4(position().x() + d_pad_input, position_.y(), 0.0f));
	}
	else {
		set_position(gef::Vector4(mouse_data.coordinates.x, position_.y(), 0.0f));
	}
	

	//Calculate the percentage value of the position of the button in relation the back bar.
	percentage_value = (position().x() - backdrop_anchor_data.bottom_left.x) / (backdrop_anchor_data.bottom_right.x - backdrop_anchor_data.bottom_left.x) * 100.0f;

	//Update the foreground image to visually display the volume.
	bar_volume.set_width((backdrop_anchor_data.bottom_right.x - backdrop_anchor_data.bottom_left.x) * (percentage_value / 100.0f));

	//Adjust position - width is scaled with respect to the centre of the image.
	bar_volume.set_position(gef::Vector4(backdrop_anchor_data.bottom_left.x + (bar_volume.width() / 2.0f), bar_volume.position().y(), bar_volume.position().z()));

	//Clamp the position of the button such that it doesn't go beyond the max and min boundaries.
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

void Slider::CalculateBackBarAnchors()
{
	//Calculate the '4' positions of the corners of the image. This is to assist in updating the value of the volume bar.
	backdrop_anchor_data.top_left = gef::Vector2(bar_backdrop.position().x() - (bar_backdrop.width() / 2.0f), bar_backdrop.position().y() + (bar_backdrop.height() / 2.0f));
	backdrop_anchor_data.bottom_left = gef::Vector2(bar_backdrop.position().x() - (bar_backdrop.width() / 2.0f), bar_backdrop.position().y() - (bar_backdrop.height() / 2.0f));

	backdrop_anchor_data.top_right = gef::Vector2(bar_backdrop.position().x() + (bar_backdrop.width() / 2.0f), bar_backdrop.position().y() + (bar_backdrop.height() / 2.0f));
	backdrop_anchor_data.bottom_right = gef::Vector2(bar_backdrop.position().x() + (bar_backdrop.width() / 2.0f), bar_backdrop.position().y() - (bar_backdrop.height() / 2.0f));

}