#include "pch.h"
#include "DeathScreen.h"
#include "PawnController.h"

DeathScreen::DeathScreen(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* input_)
	:
	Menu(platform_, renderer_, sprite_renderer_, input_)
{
}

DeathScreen::~DeathScreen()
{
}

void DeathScreen::OnEnter()
{
}

void DeathScreen::Input(float delta_time)
{
}

bool DeathScreen::Update(float delta_time)
{
	return true;
}

void DeathScreen::Render()
{
}

void DeathScreen::OnExit()
{
}
