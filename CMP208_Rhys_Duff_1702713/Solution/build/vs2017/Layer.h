#pragma once
#include "graphics/sprite.h"

enum class BackdropLayersID;

struct Layer
{
	gef::Sprite* image = nullptr;
	float layer_velocity = 0.0f;
	float depth = 0.0f;
	uint32 delta_pos = 0;
	BackdropLayersID id;

	~Layer()
	{
		if (image)
		{
			delete image;
			image = nullptr;
		}
	}
};