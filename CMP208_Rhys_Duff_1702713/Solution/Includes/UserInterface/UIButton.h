#pragma once
#include "Gameobjects/SceneComponent.h"

#include "input/touch_input_manager.h"

namespace gef
{
	class SpriteRenderer;
	class Sprite;
}

class PawnController;

struct AnchorData
{
	// @brief Button's centre point, top left, bottom left,
	// top right and bottom right anchors coordinates.
	gef::Vector2 top_left;
	gef::Vector2 bottom_left;
	gef::Vector2 top_right;
	gef::Vector2 bottom_right;
};

class MouseData;

class UIButton : public gef::Sprite
{
protected:

	UIButton(std::string text, gef::Vector2 position);

public:

	~UIButton();

	// @brief Create a new Button object.
	static UIButton* Create(std::string text, gef::Vector2 position);

	// @brief Create a new font object.
	void InitFont(gef::Platform* platform_);

	// @brief Standard class functions.

	virtual void Update(float delta_time);

	virtual void Render(gef::SpriteRenderer* sprite_renderer);
	
	// @brief Method to check if mouse is hovering over the button.
	bool IsHover(PawnController* pawn_controller);

	// @brief Class Getters.


	inline const gef::Font* GetFont() { return font; }

	inline const std::string& GetText() { return text; }


protected:

	const MouseData* mouse_data;

	// @brief Display text.
	std::string text;

	// @brief Font obj to display text info
	// to the screen.
	gef::Font* font;

	// @brief Anchors representing our 4 corners of the button.
	AnchorData anchors;

	void CalculateAnchors();



};