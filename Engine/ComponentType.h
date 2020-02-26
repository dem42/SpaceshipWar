#pragma once

#include <cstddef>

enum class ComponentType : std::size_t {
	PLAYER = 0,
	POSITION,
	VIEW,
	HEADING,
	VELOCITY,
	SHOT,
	ENEMY,
	HIT_POINTS,
	TEXT_UI_VIEW,
	_Count
};

const int COMPONENT_NOT_PRESENT = -1;