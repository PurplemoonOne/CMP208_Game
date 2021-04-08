#pragma once
#include "assets/png_loader.h"
#include "animation/animation.h"

class AssetLoader
{
public:

	// @note Default argument is NULL. In cases such as the splash screen.
	AssetLoader(gef::Platform& platform, PrimitiveBuilder* primitive_builder = nullptr);
	~AssetLoader();

	// @brief Loads a model from disc.
	// @param[in] Filepath to the model.
	gef::Mesh* LoadMesh(std::string filename);

	gef::Mesh* LoadMesh(gef::Scene* scene_object);

	 // @brief Loads the skeleton associated with an animated mesh.
	 // @param[in] String to the location of the asset.
	 // @param[in] A pointer a scene object.
	gef::Skeleton* LoadSkeleton(std::string filepath);

	// @brief Loads the skeleton associated with an animated mesh.
	// @param[in] Scene object containing the skeleton.
	// @param[in] A pointer a scene object.
	gef::Skeleton* LoadSkeleton(gef::Scene* scene_asset);

	 // @brief Loads an asset into a scene object.
	 // @param[in] A pointer to the platform.
	 // @param[in] String to the location of the asset.
	 gef::Scene* LoadSceneAssets(gef::Platform* platform, std::string filepath);

	 // @brief Loads an animation from a file.
	 // @param[in] Filepath to the animation scene file.
	 // @param[in] Filepath to the animation file.
	 gef::Animation* LoadAnimation(std::string animation_scene_filename, std::string animation_filename);

	 // @brief Handles the loading of png files.
	 gef::PNGLoader png_loader;

	 // @brief Wrapper function for handling loading textures.
	 gef::Texture* Texture(std::string filename, gef::Platform* platform);

private:

	/*..Attributes associated with this class.*/

	PrimitiveBuilder* primitive_builder;

	gef::Platform* platform;

	// @brief Looks for a mesh within a scene object and returns a pointer.
	// @param[in] Takes a pointer to a scene object.
	// @note will be invoked from within the Load Mesh method.
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

};

