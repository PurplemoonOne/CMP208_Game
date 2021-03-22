#include "pch.h"
#include "Menu.h"

Menu::Menu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* input_)
	:
	platform(platform_),
	renderer(renderer_),
	sprite_renderer(sprite_renderer_),
	input(input_)
{
}

Menu::~Menu()
{
}

void Menu::OnEnter()
{
}

void Menu::Input(float delta_time)
{
}

bool Menu::Update(float delta_time)
{
	return true;
}

void Menu::Render()
{
}

void Menu::OnExit()
{
}
