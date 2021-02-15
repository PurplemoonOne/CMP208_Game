#pragma once

#include <graphics/mesh_instance.h>


namespace gef
{
	class Renderer3D;
	class MeshInstance;
}


class PawnController;
class PrimitiveBuilder;

class Pawn3d : public gef::MeshInstance
{
public:

	/*..Constructor..*/

	Pawn3d(PawnController* pawn_controller);
	~Pawn3d();


public:

	/*..Methods public access..*/

	void Pawn3d_Init(PrimitiveBuilder* primitive_builder);

	void Render(gef::Renderer3D* renderer_3d);

protected:


private:

	PawnController* input;

};

