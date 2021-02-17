#pragma once

#include <graphics/mesh_instance.h>


namespace gef
{
	class Renderer3D;
	class MeshInstance;
}


class PrimitiveBuilder;

///A 3D gameobject supporting user input.
class Pawn : public gef::MeshInstance
{
public:

	/*..Constructor..*/

	/// @brief Constructor for the gameobject.
	/// @param[in] PawnController*	A pointer to the input handler.
	Pawn();


	~Pawn();


public:

	/*..Methods public access..*/

	void Pawn3d_Init(PrimitiveBuilder* primitive_builder);

	void Render(gef::Renderer3D* renderer_3d);

protected:


};

