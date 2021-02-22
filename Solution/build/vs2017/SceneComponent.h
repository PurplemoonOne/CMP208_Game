#pragma once

/*..Maths headers..*/
#include <maths/matrix44.h>
#include <maths/vector4.h>

namespace gef
{
	class Platform;
	class Sprite;
}

class SceneComponent
{
protected:

	SceneComponent(gef::Platform& platform_);
	~SceneComponent(){}


public:

	// @brief Returns a new pointer to this object which is allocated on the heap.
	// @param[in] Takes the current system platform as an argument.
	SceneComponent* Create(gef::Platform& platform_);


	// @brief Update this objects attributes.
	// @param[in] Delta time since last frame.
	virtual void Update(float delta_time);

public:

	// @brief Grabs the game objects position in the scene.
	// @return Returns a vector 4.
	virtual inline const gef::Vector4& GetPosition() { return position; }


	// @brief Grabs the game objects current scale in the scene.
	// @return Returns a Vector 4.
	virtual inline const gef::Vector4& GetScale() { return scale; }


	// @brief Grab the rotation values around the x-axis
	// @return Returns a Vector 4.
	virtual inline const gef::Vector4& GetRotationX() { return rotation;}


protected:

	/// @brief Builds a new transform for the gameobject, called everyframe capturing changes.
	virtual gef::Matrix44 GetFinalTransform();

	/*..Game object attributes..*/

	// @brief A 4x4 matrix representing the game objects translation.
	gef::Vector4 position;
	// @brief A 4x4 matric representing the game objects rotation.
	gef::Vector4 rotation;
	// @brief A 4x4 matric representing the game objects scale in the scene.
	gef::Vector4 scale;


};

