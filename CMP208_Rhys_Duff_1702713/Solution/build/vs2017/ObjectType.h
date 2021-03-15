#pragma once

// @brief This enum class is used for filtering collisions.
enum class ObjectType
{
	environment_ = 0x0001,
	environment_dynamic_ = 0x0002,
	dynamic_ = 0x0004,
	dynamic_friendly_ = 0x0008,
	dynamic_enemy_ = 0x0016,
	dynamic_pawn_ = 0x0032
};