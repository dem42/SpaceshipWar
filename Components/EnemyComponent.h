#pragma once

#include "Engine/Component.h"

class EnemyComponent : public Component {
public:
	EnemyComponent(const Entity& entity) : Component(ComponentType::ENEMY, entity) {}

	float timeUntilNextShotCanBeFired = 0;
};

