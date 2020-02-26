#pragma once

#include <cstddef>

enum class EnemyBehaviourType : std::size_t {
	AGGRESSIVE,
	COWARD,
	_Count,
};