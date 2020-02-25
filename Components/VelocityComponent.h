#pragma once

#include "Engine/Component.h"

class VelocityComponent : public Component {
public:
	VelocityComponent(const std::shared_ptr<Entity>& entity) : Component(ComponentType::VELOCITY, entity) {}

	float x;
	float y;
	float magnitude;
};

