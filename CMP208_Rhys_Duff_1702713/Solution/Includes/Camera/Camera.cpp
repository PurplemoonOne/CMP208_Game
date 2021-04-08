#include "pch.h"

#include "Camera.h"

//Input
#include "Input/PawnController.h"

#include "system/platform.h"

#define PI = 3.1415

Camera::Camera(gef::Platform* platform_)
	:SceneComponent(*platform_),
	platform(platform_),
	camera_target(gef::Vector4::kZero),
	camera_up(gef::Vector4::kZero)
{
	proj_matrix.SetIdentity();
	view_matrix.SetIdentity();


	//Kinematics
	camera_velocity = 1.0f;
	camera_acceleration = 1.2f;

	//Radial motion
	radial_acceleration = 1.2f;
}

Camera::~Camera()
{
}

Camera* Camera::Create(gef::Platform* platform_)
{
	return new Camera(platform_);
}

void Camera::InitialisePerspectiveMatrices()
{

	/*..Projection matrix initialisation..*/
	const float fov = gef::DegToRad(46.8f);
	const float aspect_ratio = (float)platform->width() / (float)platform->height();
	float near_plane = 0.1f;
	float far_plane = 10.0f;

	proj_matrix = platform->PerspectiveProjectionFov(fov, aspect_ratio, near_plane, far_plane);


	/*..Initialise the look at matrix..*/
	position = gef::Vector4(6.0f, 1.0f, 25.0f);
	camera_up = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_target = gef::Vector4(0.0f, -2.0f, 0.0f);

	view_matrix.LookAt(position, camera_target, camera_up);


}

void Camera::SetSceneMatrices(gef::Renderer3D* scene_3d_renderer)
{
	scene_3d_renderer->set_projection_matrix(proj_matrix);
	scene_3d_renderer->set_view_matrix(view_matrix);
}

void Camera::UpdateCameraLookAt(const gef::Vector2& mouse_coordinates, float delta_time, bool update_cam)
{

		if (update_cam)
		{
				float yaw = rotation.y();
				float pitch = rotation.x();
				float roll = rotation.z();

				const gef::Vector2 mouse_position = mouse_coordinates;

				//Calculate the change in coordinates from the screen centre.
				gef::Vector2 delta_mouse = mouse_position - gef::Vector2(platform->width() / 2.0f, platform->height() / 2.0f);

				//Update rotation.x and pitch based on mouse new coordinates.
				yaw -= delta_mouse.x * radial_acceleration * delta_time;
				pitch += delta_mouse.y * radial_acceleration * delta_time;


				//Update the camera's forward vector.
				CalculateForwardVector(yaw, pitch);
				CalculateUpVector(yaw, pitch, roll);
				CalculateRightVector();

		
		}
	
		//Update the look at matrix.
		view_matrix.LookAt(position, camera_target, camera_up);
}

void Camera::Update(float delta_time)
{
	view_matrix.LookAt(position, camera_target, camera_up);
}

void Camera::SetTarget(gef::Vector4 target)
{
	camera_target = target;
}


void Camera::CalculateForwardVector(float& yaw, float& pitch)
{
	//Calculate the forward components.
	const float forward_x = gef::RadToDeg((sinf(yaw) * cosf(pitch)));
	const float forward_y = gef::RadToDeg(sinf(pitch));
	const float forward_z = gef::RadToDeg((cosf(pitch) * cosf(yaw)));

	forward = gef::Vector4(forward_x, forward_y, forward_z);

	CalculateLookAtVector();
}

void Camera::CalculateLookAtVector()
{

	camera_target = position + forward;

}

void Camera::CalculateUpVector(float& yaw, float& pitch, float& roll)
{
	//Calculate the up vector component using the camera's rotation.x, pitch and roll values.
//	const float up_x = gef::RadToDeg(-cosf(yaw) * sinf(roll) - sinf(yaw) * sinf(pitch) * cosf(roll));
//	const float up_y = gef::RadToDeg(cosf(pitch) * cosf(roll));
//	const float up_z = gef::RadToDeg(-sinf(yaw) * sinf(roll) - sinf(pitch) * cosf(roll) * -cosf(yaw));

	up = gef::Vector4(0.0f, 1.0f, 0.0f);
}

void Camera::CalculateRightVector()
{
	//Get the cross product of forward and up.
	right = forward.CrossProduct(up);

}


