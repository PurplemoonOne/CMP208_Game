#pragma once
#include "graphics/mesh.h"


/*
* 
*	In reference to the flyweight pattern, we can 
*	load one instance of a model into memory. Then 
*	for every instance object we can point to 'this'
*	model.
* 
*/
class Model
{
protected:

	Model(gef::Mesh* mesh);

public:

	~Model();

	// @brief Create a new Model on the heap.
	static Model* Create(gef::Mesh* mesh);

	// @brief Return an const pointer to the mesh. Cannot modify this class.
	inline const gef::Mesh* GetModel() const { return mesh; }

private:

	gef::Mesh* mesh;

};

