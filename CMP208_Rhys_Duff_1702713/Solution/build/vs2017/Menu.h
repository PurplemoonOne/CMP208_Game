#pragma once
#include "State.h"

namespace gef
{
	class Renderer3D;
	class SpriteRenderer;
	class Platform;
}

class PawnController;

class Menu : public State
{
protected:

	/*..Menu variables..*/
	PawnController* input;
	gef::Renderer3D* renderer;
	gef::SpriteRenderer* sprite_renderer;
	gef::Platform* platform;

public:

	Menu(gef::Platform* platform_, gef::Renderer3D* renderer_, gef::SpriteRenderer* sprite_renderer_, PawnController* input_);
	~Menu();

	virtual void OnEnter();
	virtual void Input(float delta_time);
	virtual bool Update(float delta_time);
	virtual void Render();
	virtual void OnExit();


};

