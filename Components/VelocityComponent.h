#pragma once

#include "Engine/Component.h"

class VelocityComponent : public Component {
public:
	VelocityComponent(const std::shared_ptr<Entity>& entity) : Component(ComponentType::VELOCITY, entity) {}

	float x = 0.f;
	float y = 0.f;
	float magnitude = 0.f;

	float anomalyPullX = 0.f;
	float anomalyPullY = 0.f;
};

