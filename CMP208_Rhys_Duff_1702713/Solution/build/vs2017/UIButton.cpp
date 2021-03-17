#include "pch.h"
#include "UIButton.h"

#include "PawnController.h"


UIButton::UIButton(gef::Platform* platform_, std::string text_, gef::Vector2 position)
	:
	platform(platform_),
	font(*platform),
	text(text_)
{
	font.Load("comic_sans");
	set_width(10.f);
	set_height(10.0f);

	set_position(position.x, position.y, 0.0f);
	CalculateAnchors();

	colour_ = (16 << 255) | (8 << 0) | 0;
}

UIButton::~UIButton()
{
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
		//Animate clicked.
		break;
	case ButtonState::HOVER:
		colour_ = (16 << 255) | (8 << 255) | 0;
		break;
	default:
		colour_ = (16 << 255) | (8 << 0) | 0;
		break;
	}

}

void UIButton::Render(gef::SpriteRenderer* sr)
{
	sr->Begin(false);

		sr->DrawSprite(*this);

		font.RenderText(sr, gef::Vector4(position_.x(), position_.y(), 0.0f), 1.0f, colour_,gef::TJ_CENTRE, text.data());
	
	sr->End();
}

ButtonState UIButton::EvaluateButtonState(PawnController* pawn_controller)
{
	button_state = ButtonState::NULL_;

	const MouseData* mouse_data = &pawn_controller->GetMouseData();

	bool clicked = mouse_data->mouse_left_button_state == gef::TouchType::TT_NEW ?
		true : false;

	bool align = false;

	//Check if we're  hovering over button
	if ((mouse_data->mouse_coordinates->x > anchors.bottom_left.x) && // > bottom left x
		(mouse_data->mouse_coordinates->y < anchors.top_right.y) && // < top right y

		(mouse_data->mouse_coordinates->x < anchors.bottom_right.x) && // < bottom right x
		(mouse_data->mouse_coordinates->y > anchors.bottom_right.y)	 // > bottom right y
		)
	{
		align = true;
		gef::DebugOut("Mouse is hovering.");
	}

	//If we clicked this region of space return true.
	if (clicked && align) {
		button_state = ButtonState::CLICKED;
		gef::DebugOut("Mouse is clicked button.");
	}
	else if (align){
		button_state = ButtonState::HOVER;
	}
	//Else NULL_ but we assigned that.

	return button_state;
}

void UIButton::SetPosition(float x, float y)
{
	position_ = gef::Vector4(x, y, 0.0f);
}

void UIButton::CalculateAnchors()
{

	anchors.top_left = gef::Vector2(position_.x() - (width_ / 2.0f), position_.y() + (height_ / 2.0f));
	anchors.bottom_left = gef::Vector2(position_.x() - (width_ / 2.0f), position_.y() - (height_ / 2.0f));

	anchors.top_right = gef::Vector2(position_.x() + (width_ / 2.0f), position_.y() + (height_ / 2.0f));
	anchors.bottom_right = gef::Vector2(position_.x() + (width_ / 2.0f), position_.y() - (height_ / 2.0f));

}
