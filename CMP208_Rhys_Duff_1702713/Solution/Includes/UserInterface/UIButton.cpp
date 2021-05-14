#include "pch.h"
#include "UIButton.h"

#include "Input/PawnController.h"
#include "Audio.h"


UIButton::UIButton(std::string text_, gef::Vector4 position)
	:
	text(text_),
	is_selected(false)
{
	mouse_data = nullptr;
	font = nullptr;
	position_ = gef::Vector4(position.x(), position.y(), position.z());
	CalculateAnchors();
}

UIButton::~UIButton()
{
	if (font) {
		delete font;
		font = nullptr;
	}
}

UIButton* UIButton::Create(std::string text, gef::Vector4 position)
{
	return new UIButton(text, position);
}

void UIButton::InitFont(gef::Platform* platform_)
{
	font = new gef::Font(*platform_);
	font->Load("comic_sans");
}

void UIButton::Update(float delta_time)
{

}

void UIButton::Render(gef::SpriteRenderer* sprite_renderer)
{
	sprite_renderer->DrawSprite(*this);

	if (font != nullptr)
	{
		font->RenderText
		(
			sprite_renderer,
			gef::Vector4(position().x(), position().y(), -0.9f),
			1.0f,
			0xffffffff,
			gef::TextJustification::TJ_LEFT,
			text.c_str()
		);
	}

}

bool UIButton::IsHover(PawnController* pawn_controller, Audio* audio)
{
	CalculateAnchors();
	const MouseData* mouse_data = &pawn_controller->GetMouseData();

		//Check if we're hovering over button
	if ((mouse_data->coordinates.x > anchors.bottom_left.x) && // > bottom left x
		(mouse_data->coordinates.y < anchors.top_right.y) && // < top right y

		(mouse_data->coordinates.x < anchors.bottom_right.x) && // < bottom right x
		(mouse_data->coordinates.y > anchors.bottom_right.y)	 // > bottom right y
		)
	{
		is_selected = true;
		audio->PlaySFX(sfxid::button_click_a, false);
	}
	else
	{
		is_selected = false;
	}

	return is_selected;
}

void UIButton::CalculateAnchors()
{

	anchors.top_left = gef::Vector2(position_.x() - (width_ / 2.0f), position_.y() + (height_ / 2.0f));
	anchors.bottom_left = gef::Vector2(position_.x() - (width_ / 2.0f), position_.y() - (height_ / 2.0f));

	anchors.top_right = gef::Vector2(position_.x() + (width_ / 2.0f), position_.y() + (height_ / 2.0f));
	anchors.bottom_right = gef::Vector2(position_.x() + (width_ / 2.0f), position_.y() - (height_ / 2.0f));

}
