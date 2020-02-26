#pragma once

#include "Engine/Component.h"

class PositionComponent : public Component {
public:
	PositionComponent(const std::shared_ptr<Entity>& entity, float x, float y, float yawDegrees) : Component(ComponentType::POSITION, entity), x(x), y(y), yaw(yawDegrees) {}

	static float distanceSqrd(const PositionComponent& left, const PositionComponent& right);
	static float distance(const PositionComponent& left, const PositionComponent& right);

	float x;
	float y;
	float yaw;
};

