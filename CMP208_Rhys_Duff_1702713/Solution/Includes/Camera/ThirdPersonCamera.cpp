#include "pch.h"
#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(gef::Platform* plat)
	:
	Camera(plat),
	is_shaking(false),
	can_shake(false),
	generate_points(true)
{
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

ThirdPersonCamera* ThirdPersonCamera::Create(gef::Platform* platform_)
{
	return new ThirdPersonCamera(platform_);
}

void ThirdPersonCamera::SetTarget(gef::Vector4 target_)
{
	camera_target = gef::Vector4(target_.x(), target_.y() + 2.0f, target_.z());
	position = (target_ + gef::Vector4(0.0f, 6.0f, 20.0f));
}

void ThirdPersonCamera::CameraJitter(float delta_time)
{
	if (generate_points)
	{
		GeneratePointCloud();
		generate_points = false;
	}

	if (can_shake)
	{
		is_shaking = true;
		int element_0 = 12;
		int element_1 = 57;
		int element_2 = 24;
		int element_3 = 66;

	
		gef::Vector4 points[] =
		{
			point_cloud[element_0],
			point_cloud[element_1],
			point_cloud[element_2],
			point_cloud[element_3]
		};



		SetPosition
		(
			gef::Lerp(GetPosition().x(), points[index].x(), delta_time),
			gef::Lerp(GetPosition().y(), points[index].y(), delta_time),
			GetPosition().z()
		);
		++index;


		if (index == 4)
		{
			index = 0; 
			generate_points = true;
			is_shaking = false;
			SetCanShake(false);
		}

	}


}

#define PI 3.1415


void ThirdPersonCamera::GeneratePointCloud()
{
	//Get Position.
	gef::Vector4 current_position = GetPosition();

	//Generate a cloud sphere.
	float x = 0.0f;
	float y = 0.0f;
	float z = GetPosition().z();

	//Current angle.
	float alpha = 0.0f;

	//This is the angle to step around the circle.
	float beta = (2 * PI) / 24;

	//Generate a disc of points.
	for (int point_cloud_density = 1; point_cloud_density < 4; ++point_cloud_density)
	{
		//Repeat process to generate several rings.
		for (int step = 0; step < 24; ++step)
		{
			x = point_cloud_density * cos(alpha);
			y = point_cloud_density * sin(alpha);
			alpha += beta;

			x += GetPosition().x();
			y += GetPosition().y();

			point_cloud.push_back(gef::Vector4(x, y, z));
		}
	}
}


