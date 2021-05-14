#pragma once
#include "Utilities/AssetLoader.h"

enum class ModelID
{
	Player = 0,
	Platform,
	Ground,
	Coin,
	Gem,
	Mud,
	Grass,
	Water,
	Ice,
	Lava,
	Goal,
	SkySphere,
	max
};

enum class TextureID
{
	Slider_Foreground = 0,
	Slider_Background,
	forest_background,
	death_screen,
	death_title,
	level_complete,
	ode,
	complete,
	score,
	paused,
	health,
	right_arrow,
	right_arrow_pressed,
	left_arrow,
	left_arrow_pressed,
	left_analogue_left,
	left_analogue_right,
	left_analogue_idle,
	cross_pressed,
	cross,
	max
};

enum class ButtonTextureID
{
	Button_Play = 0,
	Button_Play_Pressed,
	Button_Options,
	Button_Options_Pressed,
	Button_Exit,
	Button_Exit_Pressed,
};

enum class BackdropLayersID
{
	layer_0 = 0,
	layer_1,
	layer_2,
	layer_3,
	layer_lights_1,
	layer_5,
	layer_6,
	layer_lights_2,
	layer_8,
	layer_9,
	layer_10,
	layer_11,
	max
};

class GraphicsData
{
protected:

	// @brief Protected constructor for creating a graphics data object.
	// @param[in] Takes a pointer to the platform.
	GraphicsData(gef::Platform* platform);

public:

	~GraphicsData();

	// @brief Static function for instantiating a new Graphics Data object on the heap.
	// @param[in] Takes a pointer to the platform.
	static GraphicsData* Create(gef::Platform* platform);

	// @brief Load textures into an array with an associated ID.
	void InitialiseTextures();
	// @brief Load models from disc and store them in an array in addition to an ID.
	void LoadModels();

	// @brief Method used to store model data in an array.
	// @param[in] Takes an id associated with the model.
	// @param[in] Stores a pointer to the mesh.
	void InsertModel(ModelID id, gef::Mesh* mesh);

	// @brief Removes the model from memory.
	// @param[in] Takes an id associated with the model.
	void DeleteModel(ModelID id);

	// @brief Store a texture object in an array.
	// @param[in] Takes an ID associated with the texture.
	// @param[in] Stores a pointer to the texture object.
	void InsertTexture(TextureID id, gef::Texture* texture);

	// @brief Removes a texture object from memory.
	// @param[in] Takes an ID associated with the texture.
	void DeleteTexture(TextureID id);

	// @brief Special method for dealing with button textures.
	// @param[in] Takes an ID associated with the texture.
	// @param[in] Stores a pointer to the texture object.
	void InsertButtonTexture(ButtonTextureID id, gef::Texture* texture);

	// @brief Removes a button texture from memory.
	// @param[in] Takes an ID to the button texture.
	void DeleteButtonTexture(ButtonTextureID id);

	// @brief Special method for storing backdrop layers.
	// @param[in] Takes an ID associated with a specific layer.
	// @param[in] Stores a pointer to a texture object.
	void InsertBackdropTexture(BackdropLayersID id, gef::Texture* texture);

	// @brief Removes a backdrop texture from memory.
	// @param[in] Takes an ID to the layer.
	void DeleteBackdropTexture(BackdropLayersID id);

	// @brief Fetches a model from the array.
	// @param[in] Takes an ID to the model.
	gef::Mesh* GetMesh(ModelID id)const { return models.at((uint32)id); }

	// @brief Fetches a texture from the texture array.
	// @param[in] Takes an ID to the texture.
	gef::Texture* GetTexture(TextureID id) const { return textures.at((uint32)id); }

	// @brief Fetches a button texture stored in the texture.
	// @param[in] Takes an ID to the button texture.
	gef::Texture* GetButtonTexture(ButtonTextureID id) const { return button_textures.at((uint32)id); }

	// @brief Fetches a layer from the layers array. 
	// @param[in] Takes an ID to the specific layer.
	gef::Texture* GetBackdropTexture(BackdropLayersID id) const { return back_drop_textures.at((uint32)id); }

	// @brief Returns a pointer to the asset loader.
	inline AssetLoader* GetAssetLoader() const { return asset_loader; }

	// @brief Deletes all models.
	void ClearMesh();
	//@brief Deletes all texture.
	void ClearTextures();

private:
	gef::Platform* platform;
	// @brief We store all possible mesh in an array.
	std::array<gef::Mesh*, 15> models;
	std::array<gef::Texture*, 25> textures;
	std::array<gef::Texture*, 6> button_textures;
	std::array<gef::Texture*, 11> back_drop_textures;
	AssetLoader* asset_loader;
};

