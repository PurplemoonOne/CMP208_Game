#include "pch.h"
#include "ParallaxBackground.h"
#include "GraphicsData.h"
#include <system/platform.h>

ParallaxBackground::ParallaxBackground(gef::Platform* platform_, GraphicsData* graphics_data)
	:
	platform(platform_)
{
	Init(graphics_data);

	float vel = 10.0f;
	for (int i = 0; i < 22; ++i)
	{
		layers.at(i)->layer_velocity = vel;
		//	If index is less than 10, reset the velocity
		//	such that the sibling image for this index
		//	shares the same velocity. 
		//	i.e image @ i = 0 EQUALS image @ i = 11.
		
		vel = ((i == 10) ? vel = 10.0f : vel += 4.5f);
	}

}

ParallaxBackground::~ParallaxBackground()
{
	for (auto& layer : layers)
	{
		if (layer)
		{
			if (layer->image)
			{
				delete layer->image;
				layer->image = nullptr;
			}
			delete layer;
			layer = nullptr;
		}
	}
}

ParallaxBackground* ParallaxBackground::Create(gef::Platform* platform, GraphicsData* graphics_data)
{
	return new ParallaxBackground(platform, graphics_data);
}

void ParallaxBackground::UpdateMenuVersion(float delta_time)
{
	int counter = 0;


		for (int index = 0; index < layers.size(); ++index)
		{
			if (this)
			{
				if (layers.at(index)->image != nullptr)
				{
					float layer_x = layers.at(index)->image->position().x();

					if (layer_x < (platform->width() + platform->width() / 2.0f))
					{
						layer_x += layers.at(index)->layer_velocity * delta_time;

						layers.at(index)->image->set_position(layer_x, (platform->height() / 2.0f) - 256.0f, layers.at(index)->depth);
					}
					else
					{
						//Place image back at 0.0f minus half the screen width.
						layers.at(index)->image->set_position((0.0f - (platform->width() / 2.0f)), (platform->height() / 2.0f) - 256.0f, layers.at(index)->depth);
					}


					if (counter < 10) {
						counter++;
					}
					else {
						counter = 0;
					}
				}
			}
		}
	
}

void ParallaxBackground::UpdateGameVersion(float delta_time)
{
}

void ParallaxBackground::Render(gef::SpriteRenderer* sprite_renderer)
{
	for (auto& layer : layers)
	{
		if (layer->image)
		{
			sprite_renderer->DrawSprite(*layer->image);
		}
	}
}

void ParallaxBackground::Init(GraphicsData* graphics_data)
{
	layers.fill(nullptr);

	float max_depth = 200.0f;
	float depth = max_depth;
	int layer = ((layers.size() - layers.size() / 2) - 1);
	for (int index = 0; index < layers.size(); ++index, --layer)
	{
		//If we're half way through grabing textures reset the layer and depth values.
		if (index == (layers.size() / 2)) {
			layer = ((layers.size() - layers.size() / 2) - 1);
			depth = max_depth;
		}

		//From element 0 to size(), store the layers from furthest away to closest.
		layers.at(index) = new Layer();
		layers.at(index)->image = new gef::Sprite();
		layers.at(index)->image->set_texture(graphics_data->GetBackdropTexture((BackdropLayersID)layer));
		layers.at(index)->id = ((BackdropLayersID)layer);

		layers.at(index)->image->set_height(platform->height() + 512);
		layers.at(index)->image->set_width(platform->width());
		if (index < ((layers.size() / 2)))
		{
			layers.at(index)->image->set_position(gef::Vector4(platform->width() / 2.0f, (platform->height() / 2.0f) + 256.0f, depth));
			layers.at(index)->depth = depth;
		}
		else
		{
			layers.at(index)->image->set_position(gef::Vector4((0.0f - (platform->width() / 2.0f)), (platform->height() / 2.0f) + 256.0f, depth));
			layers.at(index)->depth = depth;
		}
		depth -= 0.1f;
	}

}
