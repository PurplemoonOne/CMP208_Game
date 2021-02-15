#include "Camera.h"

//Maths Includes
#include "maths/math_utils.h"

//GFX
#include "graphics/renderer_3d.h"


//Platform
#include "system/platform.h"

Camera::Camera(gef::Platform* platform_)
	:platform(platform_)
{

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
	float fov = gef::DegToRad(46.8f);
	float aspect_ratio = (float)platform->width() / (float)platform->height();
	const float near_plane = 0.1f;
	const float far_plane = 10.0f;

	proj_matrix = platform->PerspectiveProjectionFov(fov, aspect_ratio, near_plane, far_plane);


	/*..Initialise the look at matrix..*/
	camera_position = gef::Vector4(0.0f, 1.0f, 5.0f);
	camera_up = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_target = gef::Vector4(0.0f, 0.0f, 0.0f);

	view_matrix.LookAt(camera_position, camera_target, camera_up);


}

void Camera::SetCameraPerspectives(gef::Renderer3D* scene_3d_renderer)
{
	scene_3d_renderer->set_projection_matrix(proj_matrix);
	scene_3d_renderer->set_view_matrix(view_matrix);
}


