#pragma once

#include "GraphicsData.h"

enum class HUD
{
	score = 0,
	lives
};

class UserInterface
{
protected:

	// @brief UI to display time remaining and current score.
	UserInterface(GraphicsData* gfx_data);

public:

	~UserInterface();

	// @brief Update the screen icons with respect to window size.
	void Update(gef::Platform* platform);

	// @brief Return a new UI.
	static UserInterface* Create(GraphicsData* gfx_data);

	void DrawScore(gef::SpriteRenderer* sprite_renderer, const int& score);

	void DrawHealth(gef::SpriteRenderer* sprite_renderer, const float& health);

	void InitFont(gef::Platform* platform);

private:

	// @brief Set icon textures.
	void Initialise();
	gef::Font* score_font;
	gef::Font* health_font;

	// @brief Array to hold screen gfx.
	std::array<gef::Sprite, 2> icons;

};

