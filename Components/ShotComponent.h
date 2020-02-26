#pragma once

#include "Engine/Component.h"

class ShotComponent : public Component {
public:
	ShotComponent(const std::shared_ptr<Entity>& entity) : Component(ComponentType::SHOT, entity) {}

	bool firedByPlayer = false;
	int reclaimsSurvived = 0;
	bool available = true;
	bool explode = false;
};

