#include "pch.h"
#include "AssetLoader.h"

AssetLoader::AssetLoader(PrimitiveBuilder* primitive_builder_, gef::Platform& platform_)
	:
	platform(&platform_),
	primitive_builder(primitive_builder_)
{
}

AssetLoader::~AssetLoader()
{
}

gef::Mesh* AssetLoader::LoadMesh(std::string filepath)
{
	//Load scene.
	gef::Scene* scene_assets_ = LoadSceneAssets(platform, filepath.data());

	gef::Mesh* mesh_ = nullptr;

	if (scene_assets_) {
		//Grab mesh
		mesh_ = GetMeshFromSceneAssets(scene_assets_);
	}
	//Delete the scene assets before returnning.
	//delete scene_assets_;

	return mesh_;
}

gef::Skeleton* AssetLoader::LoadSkeleton(std::string filepath, gef::Scene* scene)
{
	gef::Skeleton* skeleton = NULL;
	if (scene)
	{
		// check to see if there is a skeleton in the the scene file
		// if so, pull out the bind pose and create an array of matrices
		// that wil be used to store the bone transformations
		if (scene->skeletons.size() > 0)
			skeleton = scene->skeletons.front();
	}

	return skeleton;
}

gef::Scene* AssetLoader::LoadSceneAssets(gef::Platform* platform, std::string filepath)
{
	gef::Scene* scene = new gef::Scene();

	const char* file_path = filepath.c_str();

	if (scene->ReadSceneFromFile(*platform, file_path))
	{
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(*platform);
		scene->CreateMeshes(*platform);
	}
	else
	{
		delete scene;
		scene = NULL;
	}

	return scene;
}

gef::Mesh* AssetLoader::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = nullptr;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
	{
		mesh = scene->meshes.front();
	}

	return mesh;
}