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
	void Render(gef::SpriteRenderer* sprite_renderer);

private:

	bool should_update;

	void Clean(std::array<Layer*, 11>& container);

	void Init(GraphicsData* graphics_data);

	// @brief Array of sprite images.
	std::array<Layer*, 11> layers;
	std::array<Layer*, 11> layers_sibling;
	
	// @brief Pointer to system platform.
	gef::Platform* platform;
};

