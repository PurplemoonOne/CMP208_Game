#pragma once


class AssetLoader
{
public:

	AssetLoader(PrimitiveBuilder* primitive_builder, gef::Platform& platform);
	~AssetLoader();

	 gef::Mesh* LoadMesh(std::string filepath);

	 gef::Skeleton* LoadSkeleton(std::string filepath, gef::Scene* scene);

	 gef::Scene* LoadSceneAssets(gef::Platform* platform, std::string filepath);

private:

	PrimitiveBuilder* primitive_builder;

	gef::Platform* platform;

	 gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

};

