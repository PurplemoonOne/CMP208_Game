#include "Camera.h"

//Maths Includes
#include "maths/math_utils.h"

//GFX
#include "graphics/renderer_3d.h"


//Platform
#include "system/platform.h"

//Input
#include "PawnController.h"


#define PI = 3.1415

Camera::Camera(gef::Platform* platform_)
	:SceneComponent(*platform_),
	platform(platform_),
	camera_position(gef::Vector4::kZero),
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
	camera_position = gef::Vector4(4.0f, 1.0f, 2.0f);
	camera_up = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_target = gef::Vector4(0.0f, 0.0f, 0.0f);

	view_matrix.LookAt(camera_position, camera_target, camera_up);


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

				const gef::Vector2 mouse_position = mouse_coordinates;

				//Calculate the change in coordinates from the screen centre.
				gef::Vector2 delta_mouse = mouse_position - gef::Vector2(platform->width(), platform->height());

				//Update yaw and pitch based on mouse new coordinates.
				yaw += delta_mouse.x * radial_acceleration * delta_time;
				pitch += delta_mouse.y * radial_acceleration * delta_time;


				//Update the camera's forward vector.
				CalculateForwardVector();
				CalculateUpVector();
				CalculateRightVector();

				//Update the look at matrix.
				view_matrix.LookAt(camera_position, camera_target, camera_up);
		
		}
	
}

void Camera::Update(float delta_time)
{
	//Calculate the necessary components for the camera.
	CalculateForwardVector();
	CalculateUpVector();
	CalculateRightVector();

	//Calculate where the camera should face.
	CalculateLookAtVector();

	view_matrix.LookAt(camera_position, camera_target, camera_up);
}

void Camera::MoveForward(float delta_time)
{
	//Update the camera's velocity, v = u + at.
	camera_velocity += camera_acceleration * delta_time;

	//s = ut + a/2 * t^2
	gef::Vector4 position_ = camera_position;

	position_ += forward * camera_velocity * delta_time;

	camera_position = position_;
}

void Camera::MoveBackward(float delta_time)
{

	camera_velocity -= camera_acceleration * delta_time;

	//s = ut + a/2 * t^2
	gef::Vector4 position_ = camera_position;

	position_ -= forward * camera_velocity * delta_time;

	camera_position = position_;
}

void Camera::MoveRight(float delta_time)
{
	camera_velocity += camera_acceleration * delta_time;

	//s = ut + a/2 * t^2
	gef::Vector4 position_ = camera_position;

	position_ += right * camera_velocity * delta_time;

	camera_position = position_;
}

void Camera::MoveLeft(float delta_time)
{
	camera_velocity -= camera_acceleration * delta_time;

	//s = ut + a/2 * t^2
	gef::Vector4 position_ = camera_position;

	position_ -= forward * camera_velocity * delta_time;

	camera_position = position_;
}


void Camera::CalculateForwardVector()
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

	camera_target = camera_position + forward;

}

void Camera::CalculateUpVector()
{
	//Calculate the up vector component using the camera's yaw, pitch and roll values.
	const float up_x = gef::RadToDeg(-cosf(yaw) * sinf(roll) - sinf(yaw) * sinf(pitch) * cosf(roll));
	const float up_y = gef::RadToDeg(cosf(pitch) * cosf(roll));
	const float up_z = gef::RadToDeg(-sinf(yaw) * sinf(roll) - sinf(pitch) * cosf(roll) * -cosf(yaw));
}

void Camera::CalculateRightVector()
{
	//Get the cross product of forward and up.
	right = forward.CrossProduct(up);

}


