#include "pch.h"

#include "SceneComponent.h"

SceneComponent::SceneComponent(gef::Platform& platform_)
	: scale(1.0f, 1.0f, 1.0f),
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f)
{
}

SceneComponent* SceneComponent::Create(gef::Platform& platform_)
{
	return new SceneComponent(platform_);
}

void SceneComponent::Update(float delta_time)
{

}

inline void SceneComponent::SetPosition(float x_pos, float y_pos, float z_pos)
{
	position = gef::Vector4(x_pos, y_pos, z_pos);
}

inline void SceneComponent::SetRotation(float rot_x, float rot_y, float rot_z)
{
	rotation = gef::Vector4(rot_x, rot_y, rot_z);
}

inline void SceneComponent::SetScale(float scl_x, float scl_y, float scl_z)
{
	scale = gef::Vector4(scl_x, scl_y, scl_z);
}

gef::Matrix44 SceneComponent::GetFinalTransform()
{
	gef::Matrix44 scale_, rot_x, rot_y, rot_z, trans;
	gef::Matrix44 final_transform;

	//Apply the current scale value to a matrix.
	scale_.Scale(scale);

	//Set the respective standard x,y,z rotation matrices.
	rot_x.RotationX(rotation.x());
	rot_y.RotationY(rotation.y());
	rot_z.RotationZ(rotation.z());

	//Ensure no values are present in the translation matrix.
	trans.SetIdentity();
	//Then set the current position.
	trans.SetTranslation(position);

	//Finally multiply out the matrices using standard SRT method.
	final_transform = scale_ * rot_x * rot_y * rot_z * trans;

	return final_transform;
}
