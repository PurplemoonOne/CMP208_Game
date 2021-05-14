#pragma once

// @brief This enum class is used for filtering collisions.
enum class ObjectType
{
	static_ = 0x0000,
	environment_ = 0x0001,
	environment_dynamic_ = 0x0002,
	dynamic_enemy_ = 0x0004,
	dynamic_pawn_ = 0x0008,
	collectable_ = 0x0016,
	gem_ = 0x0032,
	goal_ = 0x0064,
	ice_ = 0x0128,
	water_ = 0x0256,
	lava_ = 0x0512
};