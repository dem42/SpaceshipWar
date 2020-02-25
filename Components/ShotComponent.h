#pragma once

#include "Engine/Component.h"

class ShotComponent : public Component {
public:
	ShotComponent(const Entity& entity) : Component(ComponentType::SHOT, entity) {}

	bool firedByPlayer = false;
	float age = 0;
	bool available = true;
};

