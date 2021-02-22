#include "SceneComponent.h"

SceneComponent::SceneComponent(gef::Platform& platform_)
{
}

SceneComponent* SceneComponent::Create(gef::Platform& platform_)
{
	return new SceneComponent(platform_);
}

void SceneComponent::Update(float delta_time)
{

}

gef::Matrix44 SceneComponent::GetFinalTransform()
{
	gef::Matrix44 scale_, rot_x, rot_y, rot_z, trans;
	gef::Matrix44 final_transform;

	//Apply the current scale value to a matrix.
	scale_.Scale(scale);

	//Set the respective standard x,y,z rotation matrices.
	rot_x.RotationX(rotation.x());
	rot_y.RotationX(rotation.y());
	rot_z.RotationX(rotation.z());

	//Ensure no values are present in the translation matrix.
	trans.SetIdentity();
	//Then set the current position.
	trans.SetTranslation(position);

	//Finally multiply out the matrices using standard SRT method.
	final_transform = scale_ * rot_x * rot_y * rot_z * trans;

	return final_transform;
}
