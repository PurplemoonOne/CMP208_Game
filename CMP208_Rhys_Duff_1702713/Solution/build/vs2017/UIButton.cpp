#include "pch.h"
#include "UIButton.h"

#include "PawnController.h"


UIButton::UIButton(gef::Platform* platform_, std::string text_, gef::Vector2 position)
	:
	platform(platform_),
	text(text_)
{
	font = new gef::Font(*platform);
	font->Load("comic_sans");

	set_width(100.0f);
	set_height(50.0f);

	set_position(position.x, position.y, 0.0f);
	CalculateAnchors();
}

UIButton::~UIButton()
{
	delete font;
	font = nullptr;
}

UIButton* UIButton::Create(gef::Platform* platform, std::string text, gef::Vector2 position)
{
	return new UIButton(platform, text, position);
}

void UIButton::Update(float delta_time)
{

	switch (button_state)
	{
	case ButtonState::CLICKED:

		break;
	case ButtonState::HOVER:

		break;
	default:

		break;
	}

}

void UIButton::Render(gef::SpriteRenderer* sprite_renderer)
{
	sprite_renderer->DrawSprite(*this);

	if (font)
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

ButtonState UIButton::EvaluateButtonState(PawnController* pawn_controller)
{
	button_state = ButtonState::NULL_;

	pawn_controller->ProcessTouchInput();

	const MouseData* mouse_data = &pawn_controller->GetMouseData();

	bool clicked = mouse_data->left_button_state == gef::TouchType::TT_ACTIVE ?
		true : false;

	bool align = false;

	if (mouse_data->coordinates != nullptr)
	{
		//Check if we're  hovering over button
		if ((mouse_data->coordinates->x > anchors.bottom_left.x) && // > bottom left x
			(mouse_data->coordinates->y < anchors.top_right.y) && // < top right y

			(mouse_data->coordinates->x < anchors.bottom_right.x) && // < bottom right x
			(mouse_data->coordinates->y > anchors.bottom_right.y)	 // > bottom right y
			)
		{
			align = true;
		}
	}

	//If we clicked this region of space return true.
	if (clicked && align) {
		button_state = ButtonState::CLICKED;
	}
	else if (align){
		button_state = ButtonState::HOVER;
	}
	//Else NULL_ but we assigned that.

	return button_state;
}

void UIButton::CalculateAnchors()
{

	anchors.top_left = gef::Vector2(position_.x() - (width_ / 2.0f), position_.y() + (height_ / 2.0f));
	anchors.bottom_left = gef::Vector2(position_.x() - (width_ / 2.0f), position_.y() - (height_ / 2.0f));

	anchors.top_right = gef::Vector2(position_.x() + (width_ / 2.0f), position_.y() + (height_ / 2.0f));
	anchors.bottom_right = gef::Vector2(position_.x() + (width_ / 2.0f), position_.y() - (height_ / 2.0f));

}
