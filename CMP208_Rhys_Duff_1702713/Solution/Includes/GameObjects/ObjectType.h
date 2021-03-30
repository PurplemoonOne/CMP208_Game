#pragma once

// @brief This enum class is used for filtering collisions.
enum class ObjectType
{
	static_ = 0x0000,
	environment_ = 0x0001,
	environment_dynamic_ = 0x0002,
	dynamic_enemy_ = 0x0004,
	dynamic_pawn_ = 0x0008
};