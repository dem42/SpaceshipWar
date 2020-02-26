#pragma once

#include "Engine/Component.h"
#include "Game/AI/EnemyBehaviour.h"

class EnemyComponent : public Component {
public:
	EnemyComponent(const std::shared_ptr<Entity>& entity, EnemyBehaviourType behaviourType) : Component(ComponentType::ENEMY, entity), behaviourType(behaviourType) {}

	bool active = true;

	float timeUntilNextShotCanBeFired = 0;
	EnemyBehaviourType behaviourType;
	bool shooting = false;
};

