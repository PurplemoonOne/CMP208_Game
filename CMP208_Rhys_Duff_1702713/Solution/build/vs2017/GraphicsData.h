#pragma once
#include "Utilities/AssetLoader.h"

enum class ModelID
{
	Player = 0,
	Platform,
	Ground,
	Coin,
	Gem,
	max
};

enum class TextureID
{
	Button_Play = 0,
	Button_Play_Pressed,
	Button_Options,
	Button_Options_Pressed,
	Button_Exit,
	Button_Exit_Pressed,
	Slider_Master,
	Slider_Music,
	Slider_Sfx,
	forest_background,
	max
};

class GraphicsData
{
protected:

	GraphicsData(gef::Platform* platform);

public:

	~GraphicsData();

	static GraphicsData* Create(gef::Platform* platform);

	void InitialiseTextures();

	void InsertModel(ModelID id, gef::Mesh* mesh);
	void DeleteModel(ModelID id);

	void InsertTexture(TextureID id, gef::Texture* texture);
	void DeleteTexture(TextureID id);

	gef::Mesh* GetMesh(ModelID id)const { return models.at((uint32)id); }
	gef::Texture* GetTexture(TextureID id) const { return textures.at((uint32)id); }

	inline AssetLoader* GetAssetLoader() const { return asset_loader; }

	void ClearMesh();
	void ClearTextures();

private:

	gef::Platform* platform;

	// @brief We store all possible mesh in an array.
	std::array<gef::Mesh*, 10> models;
	std::array<gef::Texture*, 20> textures;

	AssetLoader* asset_loader;

};

