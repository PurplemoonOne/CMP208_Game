#include "pch.h"
#include "LevelGenerator.h"
#include "GameObjects/GameObject.h"
#include "Physics/PhysicsComponent.h"

// Data chunk.
Chunk::Chunk(int32 id_, gef::Vector4 world_pos)
	:
	chunk_id(id_),
	true_position(world_pos)
{
	// Populate coordinates.
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			local_coordinates[i][j].is_occupied = false;
			local_coordinates[i][j].x = i + true_position.x();
			local_coordinates[i][j].y = j + true_position.y();
		}
	}

	for (int i = 0; i < game_objects.size(); ++i)
	{
		game_objects.at(i) = nullptr;
		phys_components.at(i) = nullptr;
	}

}

//Methods for generating the level.
LevelGenerator::LevelGenerator(gef::Platform* platform_)
	:
	platform(platform_)
{
	//Initialise the array.
	chunks.fill(nullptr);
}


void LevelGenerator::GenerateWorld()
{
	//Chunks attributes.
	int32 id_ = 0;
	float x_ = 0;
	float y_ = 0;

	for (int32 i = 0; i < chunks.size(); ++i)
	{
		chunks.at(i) = new Chunk(id_, gef::Vector4(x_ * 10.0f, y_ * 10.0f, 0.0f));
		//Incriment chunk id.
		id_++;

		//Incriment chunk position
		x_ += 1;
		y_ += 1;

	}
}

void LevelGenerator::GenerateWorldPlatforms(PrimitiveBuilder* primitive_builder, b2World* world)
{
	uint16 rand_x = 0;
	uint16 rand_y = 0;
	int32 rand_ = 0;	// Used to evaluate whether we should place a climable object.
	int32 index = 0;

	for (auto& chunk : chunks)
	{
		index = 0;
		for (int32 i = 0; i < chunk->game_objects.size(); ++i)
		{
			rand_ = rand() % 100 + 1;

			if (rand_ > 25)
			{
				//chunk->game_objects[index] = nullptr;
				index += 1;
			}
			else
			{
				//Create a platform object
				GameObject* climbable = GameObject::Create(*platform);

				//Now we need to assign gfx and ensure we can spawn it in a random place.
				climbable->SetMeshAsCube(primitive_builder);
				climbable->SetScale(3.0f, 1.0f, 1.0f);
				climbable->SetPosition(rand_x, rand_y, 0.0f);

				PhysicsComponent* physics = PhysicsComponent::Create(world, climbable, false);
				physics->CreateFixture(PhysicsComponent::Shape::BOX, 0.0f, 0.3f, 1.0f, false);

				//Generate a random location for the climable object.
				rand_x = (uint16)chunk->true_position.x() + rand() % 1 + 6;
				rand_y = (uint16)chunk->true_position.y() + rand() % 4 + 6;

				chunk->game_objects[index] = climbable;
				chunk->phys_components[index] = physics;
				index += 1;
			}
		}
		
	}

}


