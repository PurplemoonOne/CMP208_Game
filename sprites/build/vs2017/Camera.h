#pragma once

#include "maths/vector2.h"
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

	/// @brief Returns a new Camera object.
	static Camera* Create(gef::Platform* platform_);

	void InitialisePerspectiveMatrices();

	void CameraMatrices(gef::Renderer3D* scene_3d_renderer);

	/// @brief Grabs the cameras projection matrix in scene.
	/// @return Returns a Matrix4x4.
	inline const gef::Matrix44& CameraProjectionMatrix() { return proj_matrix; }

	/// @brief Grabs the cameras view matrix in scene.
	/// @return Returns a Matrix4x4.
	inline const gef::Matrix44& CameraViewMatrix() { return view_matrix; }

	/// @brief Grabs the cameras position in scene.
	/// @return Returns a vector 4.
	inline const gef::Vector4& GetTranslation() { return camera_position; }

	/*..Methods for calculating flying camera..*/

	/// @brief Calculates the difference in mouse position.
	/// @param[in] Mouse position on the screen.
	/// @param[in] Time since last frame.
	void UpdateCameraLookAt(const gef::Vector2& mouse_coordinates, float delta_time, bool update_cam);

	/// @brief Updates the camera's movement
	/// @param[in] Delta time since last frame.
	void UpdateCameraStrafe(float delta_time);

protected:

	/// @brief Calculate the camera's new yaw.
	void CalculateForwardVector();

	/// @brief Calculate the forward look at position.
	void CalculateLookAtVector();

	/// @brief Calculate the up vector.
	void CalculateUpVector();

	/// @brief Calculate the right vector perpindicluar to the forward and up vectors.
	void CalculateRightVector();

	/*..Fly camera attributes..*/

	float yaw;
	float pitch;
	float roll;

	float radial_acceleration;
	float camera_velocity;

	gef::Vector2 delta_mouse;

	/*..Matrix Variables..*/
	gef::Matrix44 proj_matrix;
	gef::Matrix44 view_matrix;

	/*..Camera variables..*/
	gef::Vector4 camera_position;
	gef::Vector4 camera_target;
	gef::Vector4 camera_up;

	gef::Vector4 forward;
	gef::Vector4 right;
	gef::Vector4 up;

	/*..Pointer to the current platform..*/
	gef::Platform* platform;

};


