#include "pch.h"
#include "Context.h"

Context::Context(gef::Platform& platform_)
	:
	platform(&platform_),
	state(nullptr)
{
	// @note Create the essential objects required to interact with our application.
	// Only one context can be instantiated and run.
	if (context_count == 0)
	{
		/*..Create our input devices..*/
		input_manager = gef::InputManager::Create(*platform);
		pawn_controller = PawnController::Create(*platform, input_manager);

		/*..Initialise Renderers..*/
		renderer = gef::Renderer3D::Create(*platform);
		sprite_renderer = gef::SpriteRenderer::Create(*platform);


		/*..Create our game states..*/
		GameState* game = new GameState(platform, renderer, sprite_renderer, pawn_controller);
		map["Game"] = game;
		game = nullptr;

		MainMenu* main_menu = new MainMenu(platform, renderer, sprite_renderer, png_loader, pawn_controller);
		map["MainMenu"] = main_menu;
		main_menu = nullptr;

		SplashScreen* splash_screen = new SplashScreen(platform, renderer, sprite_renderer, png_loader);
		map["Splash"] = splash_screen;
		splash_screen = nullptr;

		PauseMenu* pause_menu = new PauseMenu(platform, renderer, sprite_renderer, pawn_controller);
		map["PauseMenu"] = pause_menu;
		pause_menu = nullptr;

		DeathScreen* death_screen = new DeathScreen(platform, renderer, sprite_renderer, pawn_controller);
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

Context::~Context()
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

void Context::Transition(std::string name)
{
	if (state != nullptr) {
		this->state->OnExit();//Clear any data in the current state.
	}


	this->state = map.at(name);

	this->state->OnEnter();

	this->state->SetContext(this);
}
