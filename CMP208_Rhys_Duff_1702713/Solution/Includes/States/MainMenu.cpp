#include "pch.h"

/*..Essentials..*/
#include "MainMenu.h"
#include "UserInterface/UIButton.h"
#include "Context.h"

#include <Input/sony_controller_input_manager.h>
#include <system/platform.h>

MainMenu::MainMenu(gef::Platform* platform_)
{
	game_state = false;
	options = false;
	exit = false;

	session_clock = 0.0f;

	asset_loader = new AssetLoader(*platform_);
	tower = GameObject::Create(*platform_);
	tower->SetMesh(asset_loader->LoadMesh("../assets/Structures/building_tower_tall.scn"));
	tower->SetPosition(0.0f, 0.0f, 0.0f);
}

MainMenu::~MainMenu()
{
}

void MainMenu::OnEnter()
{
	gef::Platform* platform = context->GetPlatform();

	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = this->context->Renderer()->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.45f, 0.25f, 0.45f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);

	/*..Create our buttons..*/
	float centre_x = ((platform->width() / 4.0f));

	/*..Create tags, titles and prefixes to make appending easier..*/
	std::string tags[] = { "Play", "Options", "Exit" };
	std::string prefix = "buttons/";
	std::string suffix = ".png";
	std::string filenames[] = 
	{
		"play-pressed",
		"playYellow",
		"options-pressed",
		"optionsYellow", 
		"exit-pressed",
		"exitYellow"
	};

	float y_positions[] =
	{
		((platform->height() / 2.0f) - ((platform->height() / 4.0f))),
		((platform->height() / 2.0f)),
		((platform->height() / 2.0f) + ((platform->height() / 4.0f)))
	};

	uint32 tag_index = 0;//Need a seperate counter for our tags.

	for (uint32 index = 0; index < 6; ++index)
	{
		//Incriment our tag index.
		index == 2 || index == 4 ? tag_index++ : 0;

		UIButton* button = UIButton::Create("", gef::Vector2(centre_x, y_positions[tag_index]));

		//Append filepath.
		std::string final_path = prefix + filenames[index] + suffix;

		//Convert to C style string.
		//Fill image data with a loaded png.
		asset_loader->png_loader.Load(final_path.c_str(), *platform, image);

		//Create a texture using the populated image data.
		gef::Texture* texture = gef::Texture::Create(*platform, image);	

		button->set_texture(texture);
		button->InitFont(platform);
		button->set_height(50.0f);
		button->set_width(100.0f);
		buttons[index] = button;

		//Clear last filepath.
		final_path.clear();
	}

	camera = Camera::Create(platform);
	camera->InitialisePerspectiveMatrices();
	camera->SetTarget(gef::Vector4(0.0f, 0.0f, 0.0f));
	camera->SetPosition(4.0f, 10.0f, 0.0f);
}

void MainMenu::Input(float delta_time)
{
	PawnController* input = this->context->GetInput();

	input->GetInputManager()->Update(); //Update the input.
	input->ProcessTouchInput();

	// Simple input processing : check which state we wish to enter.
	const gef::SonyControllerInputManager* sce_manger = input->GetInputManager()->controller_input();

	if (sce_manger)
	{
			const gef::SonyController* controller = sce_manger->GetController(0);

			if (controller)
			{
					if (controller->buttons_down() == gef_SONY_CTRL_CROSS || buttons[0]->IsHover(input) &&
						input->GetMouseData().left_button_state == MouseState::CLICKED)
					{
						game_state = true;
					}
					if (controller->buttons_down() == gef_SONY_CTRL_CIRCLE || buttons[2]->IsHover(input) &&
						input->GetMouseData().left_button_state == MouseState::CLICKED)
					{
						options = true;
					}
					if (controller->buttons_down() == gef_SONY_CTRL_TRIANGLE || buttons[4]->IsHover(input) &&
						input->GetMouseData().left_button_state == MouseState::CLICKED)
					{
						exit = true;
					}

			}

	}

	

}

float new_rotation = 0.0f;
bool MainMenu::Update(float delta_time)
{
	session_clock += 1.0f * delta_time;
	for (auto& button : buttons)
	{
		button->Update(delta_time);
	}

	

	if (game_state) {
		context->Transition(States::GAME);
	}
	else if (options)
	{
		context->Transition(States::OPTIONS);
	}
	else if (exit) {
		return false;
	}


	return true;
}


void MainMenu::Render()
{
	gef::Renderer3D* renderer = this->context->Renderer();
	gef::SpriteRenderer* sprite_renderer = this->context->SpriteRenderer();

	camera->SetSceneMatrices(renderer);

	renderer->Begin(true);

		renderer->DrawMesh(*tower);

	renderer->End();

	sprite_renderer->Begin(false);


	for (UIButton* button : buttons)
	{
		button->Render(sprite_renderer);
	}

	sprite_renderer->End();

}


void MainMenu::OnExit()
{	//Clear some memory.
	session_clock = 0.0f;

	options = false;
	game_state = false;
	exit = false;

	for (auto& button : buttons){
		delete button->texture();
		delete button;
	}

	delete camera;
}
