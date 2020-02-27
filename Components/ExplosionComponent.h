#pragma once

#include "Engine/Component.h"

class ExplosionComponent : public Component {

public:
	ExplosionComponent(const std::shared_ptr<Entity>& entity) : Component(ComponentType::EXPLOSION, entity) {}

	bool active = false;
	float timeUntilHidden = 0.0f;
};