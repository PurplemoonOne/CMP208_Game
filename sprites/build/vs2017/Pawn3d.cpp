//This file.
#include "Pawn3d.h"

//Graphics includes.
#include <graphics/renderer_3d.h>
#include "primitive_builder.h"

Pawn::Pawn()
{
}

Pawn::~Pawn()
{
}


void Pawn::Pawn3d_Init(PrimitiveBuilder* primitive_builder)
{

	set_mesh(primitive_builder->GetDefaultCubeMesh());
}

void Pawn::Render(gef::Renderer3D* renderer_3d)
{
	/*..Render this object..*/

	renderer_3d->DrawMesh(*this);


}
