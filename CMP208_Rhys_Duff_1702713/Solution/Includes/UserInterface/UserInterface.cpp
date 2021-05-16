#include "pch.h"
#include "UserInterface.h"
#include "system/platform.h"

UserInterface::UserInterface(GraphicsData* gfx_data)
{

	// Create a new HUD.
	icons[0] = gef::Sprite();
	icons[0].set_texture(gfx_data->GetTexture(TextureID::score));
	icons[0].set_height(128.0f);
	icons[0].set_width(128.0f);

	// Create a new HUD.
	icons[1] = gef::Sprite();
	icons[1].set_texture(gfx_data->GetTexture(TextureID::health));
	icons[1].set_height(128.0f);
	icons[1].set_width(128.0f);
}

UserInterface::~UserInterface()
{
}

void UserInterface::Update(gef::Platform* platform)
{
	icons[0].set_position(gef::Vector4(platform->width() - 128.0f, platform->height() / 10.0f, 0.1f));
	icons[1].set_position(0.0f + 128.0f, platform->height() / 10.0f, 0.1f);
}

UserInterface* UserInterface::Create(GraphicsData* gfx_data)
{
	return new UserInterface(gfx_data);
}

void UserInterface::DrawScore(gef::SpriteRenderer* sprite_renderer, const int& score)
{
	sprite_renderer->DrawSprite(icons[0]);

	score_font->RenderText(
		sprite_renderer,
		gef::Vector4(icons[0].position().x() + 64.0f, icons[0].position().y() - 16.0f, -0.9f),
		1.0f,
		0xffffffff,
		gef::TextJustification::TJ_LEFT,
		"%i",
		score
	);
}

void UserInterface::DrawHealth(gef::SpriteRenderer* sprite_renderer, const float& health)
{
	sprite_renderer->DrawSprite(icons[1]);

	score_font->RenderText(
		sprite_renderer,
		gef::Vector4(icons[1].position().x() + 64.0f, icons[1].position().y() - 16.0f, -0.9f),
		1.0f,
		0xffffffff,
		gef::TextJustification::TJ_LEFT,
		"%i",
		(int)health
	);
}

void UserInterface::Initialise()
{
	

}

void UserInterface::InitFont(gef::Platform* platform)
{
	score_font = new gef::Font(*platform);
	score_font->Load("comic_sans");
}

