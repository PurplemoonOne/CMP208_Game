#pragma once

//Maths headers
#include "maths/vector2.h"
#include "maths/vector4.h"
#include "maths/matrix44.h"

//Scene Component
#include "SceneComponent.h"


namespace gef
{
	class Renderer3D;
	class Platform;
}

class Camera : public SceneComponent
{
protected:

	Camera(gef::Platform* platform_);

public:

	~Camera();

public:

	/// @brief Returns a new Camera object.
	static Camera* Create(gef::Platform* platform_);

	// @brief Set up the camera's attributes.
	void InitialisePerspectiveMatrices();

	/// @brief Use this method to tell the 3D renderer which view and projection matrices.
	/// @param[in] Takes a pointer to the scene's 3D renderer.
	void SetSceneMatrices(gef::Renderer3D* scene_3d_renderer);

	/// @brief Grabs the scene camera's projection matrix.
	/// @return Returns a Matrix4x4.
	inline const gef::Matrix44& CameraProjectionMatrix() { return proj_matrix; }

	/// @brief Grabs the cameras view matrix in scene.
	/// @return Returns a Matrix4x4.
	inline const gef::Matrix44& CameraViewMatrix() { return view_matrix; }

	// @brief Grab the camera's look at vector.
	inline const gef::Vector4& CameraLookAt() { return camera_target; }

	/*..Methods for calculating flying camera..*/

	/// @brief Calculates the difference in mouse position.
	/// @param[in] Mouse position on the screen.
	/// @param[in] Time since last frame.
	virtual void UpdateCameraLookAt(const gef::Vector2& mouse_coordinates, float delta_time, bool update_cam);

	/// @brief Updates the camera's properties.
	/// @param[in] Mouse position on the screen.
	/// @param[in] Time since last frame.
	void Update(float delta_time) override;

	/// @brief Updates the camera's movement
	/// @param[in] Delta time since last frame.
	//void UpdateCameraStrafe(float delta_time);



	void MoveForward(float delta_time);

	void MoveBackward(float delta_time);

	void MoveRight(float delta_time);

	void MoveLeft(float delta_time);


protected:

	/// @brief Calculate the camera's new yaw.
	void CalculateForwardVector(float& yaw, float& pitch);

	/// @brief Calculate the forward look at position.
	void CalculateLookAtVector();

	/// @brief Calculate the up vector.
	void CalculateUpVector(float& yaw, float& pitch, float& roll);

	/// @brief Calculate the right vector perpindicluar to the forward and up vectors.
	void CalculateRightVector();

	/*..Fly camera attributes..*/

	float radial_acceleration;
	float camera_velocity;
	float camera_acceleration;

	gef::Vector2 delta_mouse;

	/*..Matrix Variables..*/
	gef::Matrix44 proj_matrix;
	gef::Matrix44 view_matrix;

	/*..Camera variables..*/
	gef::Vector4 camera_target;
	gef::Vector4 camera_up;

	gef::Vector4 forward;
	gef::Vector4 right;
	gef::Vector4 up;

	/*..Pointer to the current platform..*/
	gef::Platform* platform;

};


