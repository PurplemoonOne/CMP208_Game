#include "pch.h"
#include "Model.h"


Model::Model(gef::Mesh* mesh_)
	:
	mesh(nullptr)
{
	mesh = mesh_;
}

Model::~Model()
{
	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}
}

Model* Model::Create(gef::Mesh* mesh_)
{
	return new Model(mesh_);
}

