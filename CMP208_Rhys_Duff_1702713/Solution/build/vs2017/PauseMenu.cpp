#include "pch.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* pawn_controller_)
	:
	Menu(platform_, renderer_, sprite_renderer_, pawn_controller_)
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::OnEnter()
{
}

void PauseMenu::Input(float delta_time)
{
}

bool PauseMenu::Update(float delta_time)
{
	return true;
}

void PauseMenu::Render()
{
}

void PauseMenu::OnExit()
{
}
