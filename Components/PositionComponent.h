#pragma once

#include "Engine/Component.h"

class PositionComponent : public Component {
public:
	PositionComponent(const Entity& entity, float x, float y);

	float x;
	float y;
};

