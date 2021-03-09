#pragma once
#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include "box2d/box2d.h"

/*..Pawn Include..*/
#include "Pawn3d.h"
#include "Planet.h"
/*..Camera..*/
#include "Camera.h"

class SceneHandler
{
public:

	/*
	* 
	*	The purpose of the scene handler is to load levels and instantiate objects with respect to that level.
	* 
	*/

private:

	gef::Scene* current_scene;

};

