#pragma once
#include "box2d/box2d.h"
#include "graphics/mesh_instance.h"
#include "graphics/mesh.h"

namespace gef
{
	class Renderer3D;
	class Platform;
	class MeshInstance;
	class Mesh;
}

class b2DebugDraw : public b2Draw
{
public:

	/// Draw a closed polygon provided in CCW order.
	 void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	/// Draw a solid closed polygon provided in CCW order.
	 void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	/// Draw a circle.
	 void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);

	/// Draw a solid circle.
	 void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);

	/// Draw a line segment.
	 void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	 void DrawTransform(const b2Transform& xf);

	/// Draw a point.
	 void DrawPoint(const b2Vec2& p, float size, const b2Color& color);

	 void InitialisDebugData(gef::Platform* ptr_to_platform, gef::Renderer3D* renderer);

	 // Pointer to the 3D renderer.
	 gef::Renderer3D* renderer_3d;

	 //Pointer to the platform
	 gef::Platform* platform_; 

	 //Graphics
	 gef::MeshInstance mesh_i;
	 gef::Mesh mesh;

};

