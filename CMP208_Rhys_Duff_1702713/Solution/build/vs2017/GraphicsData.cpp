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
	asset_loader = new AssetLoader(*platform);
}

GraphicsData::~GraphicsData()
{
	//Clean any data left behind.
	ClearMesh();
	ClearTextures();
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

	
	for (uint32 index = 0; index < 6; ++index)
	{
		std::string final_path = prefix + filenames[index] + suffix;											//Append filepath
		InsertTexture((TextureID)index, asset_loader->Texture(final_path, platform));							//Load the texture and store the result in the array.
	}
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