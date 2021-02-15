#pragma once

#include "maths/vector4.h"
#include "maths/matrix44.h"

namespace gef
{
	class Renderer3D;
	class Platform;
}


class Camera
{
protected:

	Camera(gef::Platform* platform_);

public:

	~Camera();

public:

	static Camera* Create(gef::Platform* platform_);

	void InitialisePerspectiveMatrices();

	void SetCameraPerspectives(gef::Renderer3D* scene_3d_renderer);

protected:


	/*..Matrix Variables..*/
	gef::Matrix44 proj_matrix;
	gef::Matrix44 view_matrix;

	/*..Camera variables..*/
	gef::Vector4 camera_position;
	gef::Vector4 camera_target;
	gef::Vector4 camera_up;

	/*..Pointer to the current platform..*/
	gef::Platform* platform;

};


