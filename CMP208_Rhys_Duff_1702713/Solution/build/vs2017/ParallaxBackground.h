#pragma once
#include "Layer.h"
#include "graphics/sprite_renderer.h"

class GraphicsData;

namespace gef
{
	class Platform;
}

class ParallaxBackground
{
protected:

	ParallaxBackground(gef::Platform* platform, GraphicsData* graphics_data);

public:

	~ParallaxBackground();

	static ParallaxBackground* Create(gef::Platform* platform, GraphicsData* graphics_data);

	void UpdateMenuVersion(float delta_time);
	void UpdateGameVersion(float delta_time);
	void Render(gef::SpriteRenderer* sprite_renderer);

private:


	void Init(GraphicsData* graphics_data);

	// @brief Array of sprite images.
	std::array<Layer*, 22> layers;
	
	// @brief Pointer to system platform.
	gef::Platform* platform;
};

