#pragma once
#pragma once
#include "Menu.h"

class PawnController;

// @brief Initial screen displayed on start up.
class PauseMenu : public Menu
{
public:

	PauseMenu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* pawn_controller_);
	~PauseMenu();

	virtual void OnEnter() override;
	virtual void Input(float delta_time)  override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:

};
