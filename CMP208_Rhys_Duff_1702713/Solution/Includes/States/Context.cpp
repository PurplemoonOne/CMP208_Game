#include "pch.h"
#include "Context.h"

Context::Context(gef::Platform& platform_)
	:
	platform(&platform_),
	state(nullptr),
	is_game_running(false),
	reset(false),
	win(false)
{
	// @note Create the essential objects required to interact with our application.
	// Only one context can be instantiated and run.
	if (context_count == 0)
	{
		/*..Create our input devices..*/
		input_manager = gef::InputManager::Create(*platform);
		pawn_controller = PawnController::Create(*platform, input_manager);

		/*..Initialise Renderers..*/
		sprite_renderer = gef::SpriteRenderer::Create(*platform);

		/*..Initialise Audio..*/
		audio = Audio::Create(*platform);
		/*..Asset loader..*/
		graphics_data = GraphicsData::Create(platform);

		graphics_data->InitialiseTextures();

		/*..Create our game states..*/
		SplashScreen* splash_screen = new SplashScreen(platform);
		map[States::SPLASH] = splash_screen;
		splash_screen = nullptr;

		MainMenu* main_menu = new MainMenu(platform);
		map[States::MAIN] = main_menu;
		main_menu = nullptr;

		GameState* game = new GameState(platform, graphics_data);
		reset = true;//When we transition for the first time we'll need to instantiate stuff.
		// @note 'reset' is set false on enter. Preventing memory leaks.
		map[States::GAME] = game;
		game = nullptr;

		PauseMenu* pause_menu = new PauseMenu(platform);
		map[States::PAUSE] = pause_menu;
		pause_menu = nullptr;

		WinLoseScreen* death_screen = new WinLoseScreen(platform);
		map[States::DEATH] = death_screen;
		death_screen = nullptr;

		Options* options = new Options(platform);
		map[States::OPTIONS] = options;
		options = nullptr;

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

	if (map.find(States::GAME) != map.end()) {
		delete map.at(States::GAME);
	}

	if (map.find(States::MAIN) != map.end()) {
		delete map.at(States::MAIN);
	}

	if (map.find(States::PAUSE) != map.end()) {
		delete map.at(States::PAUSE);
	}

	if (map.find(States::OPTIONS) != map.end()) {
		delete map.at(States::OPTIONS);
	}

	if (map.find(States::DEATH) != map.end()) {
		delete map.at(States::DEATH);
	}

	if (map.find(States::SPLASH) != map.end()) {
		delete map.at(States::SPLASH);
	}
}

void Context::Transition(States name)
{
	if (state != nullptr) {
		this->state->OnExit();//Clear any data in the current state.
	}

	this->state = map.at(name);

	this->state->SetContext(this);

	this->state->OnEnter();

}
