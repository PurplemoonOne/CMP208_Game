#pragma once


class GameObject;
class PhysicsComponent;


struct Coordinates
{
	uint16 x;
	uint16 y;
	bool is_occupied;
};

struct Chunk
{
	// @brief A chunk is a volume of space 
	// populated with game objects and is 
	// data structure
	Chunk(int32 id_, gef::Vector4 world_pos);

	// @brief Array for all the objects within this tile.
	std::array<GameObject*, 5> game_objects;
	std::array<PhysicsComponent*, 5> phys_components;

	// @brief unique numerical identifier.
	int32 chunk_id;

	// @brief local coordinate system for a tile.
	Coordinates local_coordinates[10][10];

	// @brief World coordinates for a chunk
	gef::Vector4 true_position;
};

class LevelGenerator
{
public:

	LevelGenerator(gef::Platform* platform_);

	// @brief Generates world macro elements
	void GenerateWorld();

	// @brief Generates world intermediates 
	void GenerateWorldPlatforms(PrimitiveBuilder* primitive_builder, b2World* world);

	// @brief Getter used to grab a specific chunk. i.e for rendering.
	Chunk* GetChunk(int32 id_) const { return chunks[id_]; }

	/*..Attributes..*/
	std::array<Chunk*, 1> chunks;

private:


	/*..Pointer to the platform..*/
	gef::Platform* platform;

};

