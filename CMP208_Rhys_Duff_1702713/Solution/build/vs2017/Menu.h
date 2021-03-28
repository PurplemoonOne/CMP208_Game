#pragma once
#include "State.h"

/*..Platform..*/
#include <system/platform.h>

/*..Input..*/
#include "PawnController.h"
#include <input/sony_controller_input_manager.h>

/*..Assets..*/
#include "AssetLoader.h"

/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

namespace gef
{
	class Renderer3D;
	class SpriteRenderer;
	class Platform;
}

class PawnController;
class UIButton;

class Menu : public State
{
protected:


	bool game_state;
	bool options;
	bool exit;

	float session_clock;

	gef::ImageData image;

	std::vector<UIButton*> buttons;

	AssetLoader* asset_loader;

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

