#pragma once
#include "States/Context.h"


class GameObject;
class PhysicsComponent;
class GraphicsData;
class Collectable;
class Context;

enum BlockID
{
	null_ = 0,
	mud,
	mud_col,
	grass,
	water, 
	lava,
	ice,
	coin,
	gem,
	goal,
	oscillating_platform,
	max
};

struct Chunk
{
	uint32 id;
	gef::Vector4 location;
	float distance_to_player;
	//std::array<GameObject*, 1024> blocks;
	std::vector<GameObject*> blocks;
};

class LevelGenerator
{
public:

	LevelGenerator(Context* context, b2World* world);

	/*..Attributes..*/


	std::vector<GameObject*> blocks;
	std::array<Chunk, 8> chunk;

	// @brief Update the level's attributes.
	void Update(float delta_time);

	// @brief Update the current chunks attributes.
	void UpdateChunk(float delta_time);

	// @brief Render the entire level.
	// @param[in] Takes a pointer to the 3D renderer.
	// @note this was devised as a means to test the level. See 'void RenderChunk(gef::Renderer3D* renderer)' for an optimal implementation.
	void Render(gef::Renderer3D* renderer);

	// @brief Render chunks based on how many should be rendered and where the player currently is located.
	// @param[in] Takes a pointer to the 3D renderer.
	void RenderChunk(gef::Renderer3D* renderer);

	// @brief Sort the chunks bases on the player's positional value.
	// @param[in] A const argument to the player's position
	// @param[in] A boolean to check if the player is moving.
	void EvaluateChunkToRender(const gef::Vector4& player_position, bool is_moving);

	// @brief Sets the number of tiles to be drawn in a given frame.
	// @param[in] The number of tiles to be drawn. Cannot be 0 and may not exceed the maximum number of tiles.
	void SetDrawDistance(int value);
	const int& DrawDistance() { return number_of_tiles_to_render; }

private:

	int number_of_tiles_to_render;
	uint32 current_chunk_id;
	AudioEmitter audio_emitter;

	// @brief Break the level into tiles to ease the number of draw calls per frame.
	void SplitLevel();

	// @brief Generate the level.
	void Initialise(Context* context,b2World* world);

	/*..Pointer to the platform..*/
	Context* context;
};

