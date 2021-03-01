#include "pch.h"
#include "b2DebugDraw.h"
#include "graphics/renderer_3d.h"
#include "system/platform.h"

void b2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<gef::Vector4> vertices_;

	//Iterate through number of vertices.
	for (uint32 vertex_index = 0; vertex_index < vertexCount; ++vertex_index)
	{
		vertices_.push_back(gef::Vector4(vertices[vertex_index].x, vertices[vertex_index].y, 0.0f));
	}

	if (mesh.InitVertexBuffer(*platform_, vertices_.data(), vertexCount, 4, true))
	{
		
		mesh_i.set_mesh(&mesh);

		renderer_3d->DrawMesh(mesh_i);
	}

}

void b2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void b2DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
}

void b2DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
}

void b2DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void b2DebugDraw::DrawTransform(const b2Transform& xf)
{
}

void b2DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}

void b2DebugDraw::InitialisDebugData(gef::Platform* ptr_to_platform, gef::Renderer3D* renderer)
{
	platform_ = ptr_to_platform;
	renderer_3d = renderer;
}
