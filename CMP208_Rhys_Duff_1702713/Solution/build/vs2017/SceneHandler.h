#pragma once
#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include "graphics/scene.h"
#include "box2d/box2d.h"

/*..Pawn Include..*/
#include "Pawn.h"
#include "Planet.h"
/*..Camera..*/
#include "Camera.h"
#include "ThirdPersonCamera.h"

class SceneHandler
{
public:

	/*
	* 
	*	The purpose of the scene handler is to load levels and instantiate objects with respect to that level.
	* 
	*/

	SceneHandler();
	~SceneHandler();

	void PushGameObjects(const GameObject& gameObject);

	void PushTextures(const gef::Texture* texture);

	void PushMaterials(const gef::Material* texture);

private:

	gef::Scene current_scene;

};

