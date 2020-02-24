#pragma once

#include "Engine/Component.h"

class PositionComponent : public Component {
public:
	PositionComponent(const Entity& entity, float x, float y) : Component(entity), x(x), y(y) {}

	float x;
	float y;
};

