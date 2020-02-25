#pragma once

#include "Engine/Component.h"

class ShotComponent : public Component {
public:
	ShotComponent(const std::shared_ptr<Entity>& entity) : Component(ComponentType::SHOT, entity) {}

	bool firedByPlayer = false;
	float age = 0;
	bool available = true;
};

