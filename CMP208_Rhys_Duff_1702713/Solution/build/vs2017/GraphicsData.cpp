#include "pch.h"
#include "GraphicsData.h"
#include "system/platform.h"

GraphicsData::GraphicsData(gef::Platform* platform_)
	:
	platform(platform_)
{
	//Fill each array with nullptr status.
	std::fill(models.begin(), models.end(), nullptr);
	std::fill(textures.begin(), textures.end(), nullptr);
	std::fill(back_drop_textures.begin(), back_drop_textures.end(), nullptr);
	std::fill(button_textures.begin(), button_textures.end(), nullptr);
	asset_loader = new AssetLoader(*platform);
}

GraphicsData::~GraphicsData()
{
	//Clean any data left behind.
	ClearMesh();
	ClearTextures();

	delete asset_loader;
	asset_loader = nullptr;
}

GraphicsData* GraphicsData::Create(gef::Platform* platform)
{
	return new GraphicsData(platform);
}

void GraphicsData::InitialiseTextures()
{
	/*..Load textures into the arrays..*/
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

	//Load Button Textures.
	for (uint32 index = 0; index < 6; ++index)
	{
		std::string final_path = prefix + filenames[index] + suffix;											//Append filepath
		InsertButtonTexture((ButtonTextureID)index, asset_loader->Texture(final_path, platform));		
		final_path.clear();//Load the texture and store the result in the array.
	}

	//Load Generic Textures
	InsertTexture(TextureID::forest_background, asset_loader->Texture("forest_background/menu_backdrop.png", platform));
	InsertTexture(TextureID::ode, asset_loader->Texture("ode.png", platform));
	InsertTexture(TextureID::death_screen, asset_loader->Texture("death_screen.png", platform));
	InsertTexture(TextureID::level_complete, asset_loader->Texture("level_complete.png", platform));
	InsertTexture(TextureID::death_title, asset_loader->Texture("you_died.png", platform));
	InsertTexture(TextureID::score, asset_loader->Texture("score.png", platform));
	InsertTexture(TextureID::paused, asset_loader->Texture("pause.png", platform));
	InsertTexture(TextureID::health, asset_loader->Texture("Health.png", platform));
	InsertTexture(TextureID::Slider_Background, asset_loader->Texture("buttons/volume_bg.png", platform));
	InsertTexture(TextureID::Slider_Foreground, asset_loader->Texture("buttons/volume_bar.png", platform));

	//Load controller icons
	InsertTexture(TextureID::left_arrow, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Directional Arrows/ps_left_arrow.png", platform));
	InsertTexture(TextureID::left_arrow_pressed, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Directional Arrows/ps_left_arrow_p.png", platform));
	InsertTexture(TextureID::right_arrow, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Directional Arrows/ps_right_arrow.png", platform));
	InsertTexture(TextureID::right_arrow_pressed, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Directional Arrows/ps_right_arrow_p.png", platform));
	InsertTexture(TextureID::left_analogue_left, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Analogue L Inputs/ps_analogue_left.png", platform));
	InsertTexture(TextureID::left_analogue_idle, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Analogue L Inputs/ps_analogue_idle.png", platform));
	InsertTexture(TextureID::left_analogue_right, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Analogue L Inputs/ps_analogue_right.png", platform));
	InsertTexture(TextureID::cross, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Main Buttons/ps_cross.png", platform));
	InsertTexture(TextureID::cross_pressed, asset_loader->Texture("PS4 BUTTONS - Premium Assets/Main Buttons/ps_cross_p.png", platform));


	//Load backdrop images.
	prefix.clear();
	prefix = "forest_background/";
	std::string file_path[] =
	{
		"layer_0",
		"layer_1",
		"layer_2",
		"layer_3",
		"layer_4",
		"layer_5",
		"layer_6",
		"layer_7",
		"layer_8",
		"layer_9",
		"layer_10",
	};

	suffix.clear();
	suffix = ".png";

	//Loop over the ids. Store the textures in the backdrop array.
	for (int index = 0; index < back_drop_textures.size(); ++index)
	{
		std::string final_path = prefix + file_path[index] + suffix;
		InsertBackdropTexture((BackdropLayersID)index, asset_loader->Texture(final_path, platform));
		final_path.clear();
	}
	
}

void GraphicsData::LoadModels()
{

	/*..Load Models and Store them in the array..*/
	//@note This is only executed when we enter a fresh game state.
	//Upon Death assets are unloaded or when a level transitions assets
	//not used would be unloaded.
	InsertModel(ModelID::Player, asset_loader->LoadMesh("../assets/Robot/robot.scn"));
	InsertModel(ModelID::Coin, asset_loader->LoadMesh("../assets/coin.scn"));
	InsertModel(ModelID::Gem, asset_loader->LoadMesh("../assets/gem.scn"));
	InsertModel(ModelID::Mud, asset_loader->LoadMesh("../assets/Structures/mud.scn"));
	InsertModel(ModelID::Ice, asset_loader->LoadMesh("../assets/Structures/ice.scn"));
	InsertModel(ModelID::Grass, asset_loader->LoadMesh("../assets/Structures/grass.scn"));
	InsertModel(ModelID::Lava, asset_loader->LoadMesh("../assets/Structures/lava.scn"));
	InsertModel(ModelID::Water, asset_loader->LoadMesh("../assets/Structures/water.scn"));
	InsertModel(ModelID::Goal, asset_loader->LoadMesh("../assets/Structures/portal.scn"));
	InsertModel(ModelID::SkySphere, asset_loader->LoadMesh("../assets/skysphere.scn"));
}



void GraphicsData::InsertModel(ModelID id, gef::Mesh* mesh)
{
	//Store models based on their integer value.
	if (models[(uint32)id] == nullptr)
		models[(uint32)id] = mesh;
	else
		return;
}

void GraphicsData::DeleteModel(ModelID id)
{
	delete models[(uint32)id];
	models[(uint32)id] = nullptr;
}

void GraphicsData::InsertTexture(TextureID id, gef::Texture* texture)
{
	if (textures[(uint32)id] == nullptr)
		textures[(uint32)id] = texture;
	else
		return;
}

void GraphicsData::DeleteTexture(TextureID id)
{
	delete textures[(uint32)id];
	textures[(uint32)id] = nullptr;
}

void GraphicsData::InsertButtonTexture(ButtonTextureID id, gef::Texture* texture)
{
	if (button_textures[(uint32)id] == nullptr)
		button_textures[(uint32)id] = texture;
	else
		return;
}

void GraphicsData::DeleteButtonTexture(ButtonTextureID id)
{
	delete button_textures[(uint32)id];
	button_textures[(uint32)id] = nullptr;
}

void GraphicsData::InsertBackdropTexture(BackdropLayersID id, gef::Texture* texture)
{
	if (back_drop_textures[(uint32)id] == nullptr)
		back_drop_textures[(uint32)id] = texture;
	else
		return;
}

void GraphicsData::DeleteBackdropTexture(BackdropLayersID id)
{
	delete back_drop_textures[(uint32)id];
	back_drop_textures[(uint32)id] = nullptr;
}

void GraphicsData::ClearMesh()
{
	for (auto& mesh : models)
	{
		if (mesh != nullptr)
		{
			delete mesh;
			mesh = nullptr;
		}
	}
}

void GraphicsData::ClearTextures()
{
	for (auto& texture : textures)
	{
		if (texture != nullptr)
		{
			delete texture;
			texture = nullptr;
		}
	}
}