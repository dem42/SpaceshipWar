#pragma once

#include "Engine/Component.h"
#include "Game/AI/AiParams.h"

class EnemyComponent : public Component {
public:
	EnemyComponent(const std::shared_ptr<Entity>& entity, const AiParams& aiParams) 
		: Component(ComponentType::ENEMY, entity), aiParams(aiParams) {}

	bool active = true;
	float timeUntilNextShotCanBeFired = 0;	
	bool shooting = false;
	AiParams aiParams;
	

	bool isReadyToReact(float dt, float reactDeadline);

private:
	float timeUntilReact = 0.0f;
};

