#include "pch.h"
#include "AssetLoader.h"
#include "graphics/image_data.h"

AssetLoader::AssetLoader(gef::Platform& platform_, PrimitiveBuilder* primitive_builder_)
	:
	platform(&platform_),
	primitive_builder(primitive_builder_)
{
}

AssetLoader::~AssetLoader()
{
}

gef::Mesh* AssetLoader::LoadMesh(std::string filename)
{
	gef::Scene* scene_assets_ = LoadSceneAssets(platform, filename);

	gef::Mesh* mesh = nullptr;

	if (scene_assets_)
	{
		//The scene object must have the model data within it.
		mesh = GetMeshFromSceneAssets(scene_assets_);
	}
	else
	{
		gef::DebugOut("Scene file %s failed to load\n", filename);
	}

	//Return the mesh data or NULL.
	return mesh;
}

gef::Mesh* AssetLoader::LoadMesh(gef::Scene* scene_assets_)
{

	gef::Mesh* mesh = nullptr;

	if (scene_assets_)
	{
		//The scene object must have the model data within it.
		mesh = GetMeshFromSceneAssets(scene_assets_);
	}
	else
	{
		gef::DebugOut("Scene file %s failed to load\n", scene_assets_);
	}

	//Return the mesh data or NULL.
	return mesh;
}

gef::Skeleton* AssetLoader::LoadSkeleton(std::string filepath)
{
	gef::Skeleton* skeleton = NULL;

	gef::Scene* scene_assets_ = LoadSceneAssets(platform, filepath.data());

	if (scene_assets_)
	{
		// check to see if there is a skeleton in the the scene file
		// if so, pull out the bind pose and create an array of matrices
		// that wil be used to store the bone transformations
		if (scene_assets_->skeletons.size() > 0)
			skeleton = scene_assets_->skeletons.front();
	}

	return skeleton;
}

gef::Skeleton* AssetLoader::LoadSkeleton(gef::Scene* scene_assets_)
{
	gef::Skeleton* skeleton = NULL;

	if (scene_assets_)
	{
		// check to see if there is a skeleton in the the scene file
		// if so, pull out the bind pose and create an array of matrices
		// that wil be used to store the bone transformations
		if (scene_assets_->skeletons.size() > 0)
			skeleton = scene_assets_->skeletons.front();
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

gef::Animation* AssetLoader::LoadAnimation(std::string animation_scene_filename, std::string animation_filename)
{
	gef::Animation* anim = NULL;

	gef::Scene anim_scene;
	if (anim_scene.ReadSceneFromFile(*platform, animation_scene_filename.c_str()))
	{
		// if the animation name is specified then try and find the named anim
		// otherwise return the first animation if there is one
		std::map<gef::StringId, gef::Animation*>::const_iterator anim_node_iter;
		if (animation_filename.c_str())
			anim_node_iter = anim_scene.animations.find(gef::GetStringId(animation_filename.c_str()));
		else
			anim_node_iter = anim_scene.animations.begin();

		if (anim_node_iter != anim_scene.animations.end())
			anim = new gef::Animation(*anim_node_iter->second);
	}

	return anim;
}

gef::Texture* AssetLoader::Texture(std::string filename, gef::Platform* platform)
{
	gef::ImageData image;
	png_loader.Load(filename.c_str(), *platform, image);
	gef::Texture* texture = gef::Texture::Create(*platform, image);
	return texture;
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