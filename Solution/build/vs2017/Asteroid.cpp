#include "pch.h"
#include "Asteroid.h"
#include "system/debug_log.h"

static uint32_t mesh_instance_count = 0;

Asteroid::Asteroid(gef::Platform& platform_, b2World* world_, bool is_dynamic)
	:GameObject(platform_, world_, is_dynamic)
{
	mesh_instance_count++;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Render(gef::Renderer3D* renderer)
{
	
}

void Asteroid::Update(float delta_time)
{
}

Asteroid* Asteroid::Create(gef::Platform& platform_, b2World* world_, bool is_dynamic)
{
	return new Asteroid(platform_, world_, is_dynamic);
}

void Asteroid::SetMeshFromDisc(PrimitiveBuilder* primitive_builder, std::string filepath)
{

	if (!EvaluateStaticMeshInstances())
	{

		const char* scene_asset_filename = filepath.data();

	//	scene_assets_ = LoadSceneAssets(platform, scene_asset_filename);
		if (true)//FIX
		{
		//	set_mesh(GetMeshFromSceneAssets(scene_assets_));
			gef::Matrix44 trans;
			gef::Matrix44 final_;
			gef::Matrix44 rotX;
			trans.SetIdentity();
			trans.SetTranslation(gef::Vector4(0.0f, -3.0f, 8.0f));

			rotX.RotationY(90.0f);

			final_ = rotX * trans;

			set_transform(final_);
		}
		else
		{
			gef::DebugOut("Scene file %s failed to load\n", scene_asset_filename);
		}

	}
	else
	{

	}

}

inline bool Asteroid::EvaluateStaticMeshInstances()
{
	if (mesh_instance_count != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
