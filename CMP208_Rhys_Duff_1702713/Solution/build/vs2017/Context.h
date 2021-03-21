#pragma once

#include "State.h"
#include "GameState.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "DeathScreen.h"
#include "PauseMenu.h"

static UInt32 context_count = 0;


class Context
{
private:

	/*..Store our state instances in a map object..*/
	std::map<std::string, State*> map;

	/*..Pointer to our current state..*/
	State* state;

	/*..Application Variables..*/
	gef::Renderer3D* renderer;
	gef::SpriteRenderer* sprite_renderer;
	gef::Platform* platform;
	gef::PNGLoader* png_loader;
	gef::InputManager* input_manager;

public:

	Context(gef::Platform& platform_)
		:
		platform(&platform_),
		state(nullptr)
	{
		if (context_count == 0)
		{
			/*..Create our input devices..*/
			input_manager = gef::InputManager::Create(*platform);

			/*..Initialise Renderers..*/
			renderer = gef::Renderer3D::Create(*platform);
			sprite_renderer = gef::SpriteRenderer::Create(*platform);

			/*..Create our game states..*/
			GameState* game = new GameState(platform, renderer, sprite_renderer, input_manager);
			map["Game"] = game;
			game = nullptr;

			MainMenu* main_menu = new MainMenu(platform, renderer, sprite_renderer);
			map["MainMenu"] = main_menu;
			main_menu = nullptr;

			SplashScreen* splash_screen = new SplashScreen(platform, renderer, sprite_renderer, png_loader);
			map["Splash"] = splash_screen;
			splash_screen = nullptr;

			PauseMenu* pause_menu = new PauseMenu(platform, renderer, sprite_renderer, input_manager);
			map["PauseMenu"] = pause_menu;
			pause_menu = nullptr;

			DeathScreen* death_screen = new DeathScreen(platform, renderer, sprite_renderer);
			map["Death"] = death_screen;
			death_screen = nullptr;

			context_count++;
		}
		else
		{
			gef::DebugOut("There is already a game context running! Please don't instantiate more than '1' context.");
			delete this;
		}
		
	}

	~Context()
	{
		// @note This method may a bit risky on cleaning up states.
		// However I chose this method, over having a pointer to each state,
		// to reduce overall size of 'this' file.
		if (map.find("Game") != map.end()) {
			delete map.at("Game");
		}

		if (map.find("MainMenu") != map.end()) {
			delete map.at("MainMenu");
		}

		if (map.find("PauseMenu") != map.end()) {
			delete map.at("PauseMenu");
		}

		if (map.find("Death") != map.end()) {
			delete map.at("Death");
		}

		if (map.find("Splash") != map.end()) {
			delete map.at("Splash");
		}
	}

	void Transition(std::string name)
	{
		if (state != nullptr) {
			this->state->OnExit();
		}

		this->state = map.at(name);

		this->state->OnEnter();

		this->state->SetContext(this);
	}


	//@brief return the application's current state.
	inline State* CurrentState() const { return state; }

//	inline gef::InputManager* GetInput() const { return input; }

};