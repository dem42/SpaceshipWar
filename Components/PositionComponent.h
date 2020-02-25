#pragma once

#include "Engine/Component.h"

class PositionComponent : public Component {
public:
	PositionComponent(const Entity& entity, float x, float y, float yawDegrees) : Component(ComponentType::POSITION, entity), x(x), y(y), yaw(yawDegrees) {}

	float x;
	float y;
	float yaw;
};

