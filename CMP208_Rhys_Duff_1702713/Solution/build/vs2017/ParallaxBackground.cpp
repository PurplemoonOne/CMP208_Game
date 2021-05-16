#include "pch.h"
#include "ParallaxBackground.h"
#include "GraphicsData.h"
#include <system/platform.h>

ParallaxBackground::ParallaxBackground(gef::Platform* platform_, GraphicsData* graphics_data)
	:
	platform(platform_),
	should_update(true)
{
	Init(graphics_data);
}

ParallaxBackground::~ParallaxBackground()
{
	should_update = false;
	Clean(layers);
	Clean(layers_sibling);
}

ParallaxBackground* ParallaxBackground::Create(gef::Platform* platform, GraphicsData* graphics_data)
{
	return new ParallaxBackground(platform, graphics_data);
}

void ParallaxBackground::UpdateMenuVersion(float delta_time)
{


		for (int index = 0; index < layers.size(); ++index)
		{
			
				if (layers.at(index))
				{
					//Read the layer's 'x' positional.
					float pos_x = layers.at(index)->image->position().x();

					if (pos_x < (platform->width() + (platform->width() / 2.0f)))
					{
						pos_x += layers.at(index)->layer_velocity * delta_time;
						layers.at(index)->image->set_position(pos_x, (platform->height() / 2.0f) - 256.0f, layers.at(index)->depth);
					}
					else
					{
						//Place image back at 0.0f minus half the screen width.
						layers.at(index)->image->set_position((0.0f - (platform->width() / 2.0f)), (platform->height() / 2.0f) - 256.0f, layers.at(index)->depth);
					}

				}
				if (layers_sibling.at(index)->image != nullptr)
				{
					//Read the layer's 'x' positional.
					float pos_x = layers_sibling.at(index)->image->position().x();

					if (pos_x < (platform->width() + (platform->width() / 2.0f)))
					{
						pos_x += layers_sibling.at(index)->layer_velocity * delta_time;
						layers_sibling.at(index)->image->set_position(pos_x, (platform->height() / 2.0f) - 256.0f, layers_sibling.at(index)->depth);
					}
					else
					{
						//Place image back at 0.0f minus half the screen width.
						layers_sibling.at(index)->image->set_position((0.0f - (platform->width() / 2.0f)), (platform->height() / 2.0f) - 256.0f, layers_sibling.at(index)->depth);
					}

				
				}
		}
}

void ParallaxBackground::Render(gef::SpriteRenderer* sprite_renderer)
{
	for (int index = 0; index < layers.size(); ++index)
	{
		if (layers[index])
		{
			sprite_renderer->DrawSprite(*layers[index]->image);
		}
		if (layers_sibling[index])
		{
			sprite_renderer->DrawSprite(*layers_sibling[index]->image);
		}
	}
	
}

void ParallaxBackground::Clean(std::array<Layer*, 11>& container)
{
	for (auto& layer : container)
	{
		if (layer)
		{
			delete layer;
			layer = nullptr;
		}
	}
}

void ParallaxBackground::Init(GraphicsData* graphics_data)
{
	layers.fill(nullptr);

	float max_depth = 1.1f;
	float depth = max_depth;
	int layer = 10;

	//Layer velocities.
	float vel[] =
	{
		100.0f,
		95.0f,
		90.0f,
		85.0f,
		80.0f,
		75.0f,
		70.0f,
		65.0f,
		60.0f,
		55.0f,
		50.0f,
	};


	for (int index = 0; index < layers.size(); ++index, --layer)
	{
		//From element 0 to size(), store the layers from furthest away to closest.
		layers.at(index) = new Layer();																			  //Creating a new layer object.
		layers.at(index)->image = new gef::Sprite();															 //Creating a new sprite object.
		layers.at(index)->image->set_texture(graphics_data->GetBackdropTexture((BackdropLayersID)layer));		//Applying texture
		layers.at(index)->id = ((BackdropLayersID)layer);												   
		layers.at(index)->layer_velocity = vel[layer];
		//Dimensions
		layers.at(index)->image->set_height(platform->height() + 512);
		layers.at(index)->image->set_width(platform->width());
		//Position
		layers.at(index)->image->set_position(gef::Vector4(platform->width() / 2.0f, (platform->height() / 2.0f) + 256.0f, depth));
		layers.at(index)->depth = depth;

		//Repeat process for the counterpart images.
		
		//From element 0 to size(), store the layers from furthest away to closest.
		layers_sibling.at(index) = new Layer();																			  //Creating a new layer object.
		layers_sibling.at(index)->image = new gef::Sprite();															 //Creating a new sprite object.
		layers_sibling.at(index)->image->set_texture(graphics_data->GetBackdropTexture((BackdropLayersID)layer));		//Applying texture
		layers_sibling.at(index)->id = ((BackdropLayersID)layer);
		layers_sibling.at(index)->layer_velocity = vel[layer];
		//Dimensions
		layers_sibling.at(index)->image->set_height(platform->height() + 512);
		layers_sibling.at(index)->image->set_width(platform->width());
		//Position
		layers_sibling.at(index)->image->set_position(gef::Vector4(0.0f - platform->width() / 2.0f, (platform->height() / 2.0f) + 256.0f, depth));
		layers_sibling.at(index)->depth = depth;

		depth -= 0.1f;
	}

}
