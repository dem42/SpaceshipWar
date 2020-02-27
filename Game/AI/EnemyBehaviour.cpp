#include "Game/AI/EnemyBehaviour.h"

#include <iostream>

#include "Engine/Utils.h"
#include "Game/Scene.h"
#include "Game/Constants.h"
#include "Components/EnemyComponent.h"

EnemeyBehaviourMap EnemyBehaviour::behaviourMap;

EnemyBehaviour::EnemyBehaviour(EnemyBehaviourType type) : type(type)
{
}

EnemyBehaviourType EnemyBehaviour::getType() const
{
	return type;
}


float getDistanceSqrd(const EnemyComponent& enemyComponent, Scene& scene)
{
	auto& playerEntity = scene.playerEntity;
	const auto& playerPosition = scene.positions.getComponent(*playerEntity);
	const auto& enemyPosition = scene.positions.getComponent(enemyComponent.getEntity());

	float distanceToPlayer = PositionComponent::distanceSqrd(playerPosition, enemyPosition);

	return distanceToPlayer;
}


class AggressiveBehaviour : public EnemyBehaviour {
public:
	AggressiveBehaviour() : EnemyBehaviour(EnemyBehaviourType::AGGRESSIVE) {}

	void act(EnemyComponent& enemyComponent, float dt, Scene& scene, const std::shared_ptr<RandomnessSource>& rand) const final override
	{		
		const float CRITICAL_DISTANCE = 4000.0f;
		float distanceToPlayer = getDistanceSqrd(enemyComponent, scene) / enemyComponent.aiParams.distanceFactor;

		const auto& playerPosition = scene.positions.getComponent(*scene.playerEntity);
		auto& enemyHeading = scene.headings.getComponent(enemyComponent.getEntity());
		const auto& enemyVelocity = scene.velocities.getComponent(enemyComponent.getEntity());
		const auto& enemyPosition = scene.positions.getComponent(enemyComponent.getEntity());

		if (distanceToPlayer < CRITICAL_DISTANCE) {
			float x = playerPosition.x - enemyPosition.x;
			float y = playerPosition.y - enemyPosition.y;
			float mag = std::sqrt(x*x + y * y);
			x /= mag;
			y /= mag;
			// follow the player at minimal thrust
			enemyHeading.xHeading = enemyPosition.x + x;
			enemyHeading.yHeading = enemyPosition.y + y;
		}
		else {
			// follow the player at full thrust
			enemyHeading.xHeading = playerPosition.x;
			enemyHeading.yHeading = playerPosition.y;
		}
		
		float toPlayerX = playerPosition.x - enemyPosition.x;
		float toPlayerY = playerPosition.y - enemyPosition.y;
		float dotProd = toPlayerX * enemyVelocity.x + toPlayerY * enemyVelocity.y;
		
		enemyComponent.shooting = dotProd > 0;	
	}	
};


EnemeyBehaviourMap::EnemeyBehaviourMap() : behaviourMap() {
	using std::size_t;
	behaviourMap[static_cast<size_t>(EnemyBehaviourType::AGGRESSIVE)] = std::make_unique<AggressiveBehaviour>();
}

const EnemyBehaviour * EnemeyBehaviourMap::getBehaviour(EnemyBehaviourType type) const
{
	return behaviourMap[static_cast<size_t>(type)].get();
}