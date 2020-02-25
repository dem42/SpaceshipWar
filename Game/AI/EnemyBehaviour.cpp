#include "Game/AI/EnemyBehaviour.h"

#include "Game/Scene.h"
#include "Components/EnemyComponent.h"

EnemeyBehaviourMap EnemyBehaviour::behaviourMap;

EnemyBehaviour::EnemyBehaviour(EnemyBehaviourType type) : type(type)
{
}

EnemyBehaviourType EnemyBehaviour::getType() const
{
	return type;
}


class AggressiveBehaviour : public EnemyBehaviour {
public:
	AggressiveBehaviour() : EnemyBehaviour(EnemyBehaviourType::AGGRESSIVE) {}

	void act(EnemyComponent& enemyComponent, float dt, Scene& scene) const override
	{
		const float COS_ANGLE_TO_SHOOT = 0.5;
		auto& playerEntity = scene.playerEntity;
		const auto& playerPosition = scene.positions.getComponent(*playerEntity);
		
		auto& enemyHeading = scene.headings.getComponent(enemyComponent.getEntity());
		enemyHeading.xHeading = playerPosition.x;
		enemyHeading.yHeading = playerPosition.y;

		const auto& enemyVelocity = scene.velocities.getComponent(enemyComponent.getEntity());
		const auto& enemyPosition = scene.positions.getComponent(enemyComponent.getEntity());

		float toPlayerX = playerPosition.x - enemyPosition.x;
		float toPlayerY = playerPosition.y - enemyPosition.y;

		float dotProd = toPlayerX * enemyVelocity.x + toPlayerY * enemyVelocity.y;
		
		enemyComponent.shooting = dotProd > 0;	
	}
};

class CowardBehaviour : public EnemyBehaviour {
public:
	CowardBehaviour() : EnemyBehaviour(EnemyBehaviourType::COWARD) {}

	void act(EnemyComponent& enemyComponent, float dt, Scene& scene) const override
	{
		auto& playerEntity = scene.playerEntity;
		const auto& playerPosition = scene.positions.getComponent(*playerEntity);

		auto& enemyHeading = scene.headings.getComponent(enemyComponent.getEntity());
		const auto& enemyPosition = scene.positions.getComponent(enemyComponent.getEntity());

		enemyHeading.xHeading = -2*(playerPosition.x - enemyPosition.x);
		enemyHeading.yHeading = -2*(playerPosition.y - enemyPosition.y);
	}
};


EnemeyBehaviourMap::EnemeyBehaviourMap() : behaviourMap() {
	using std::size_t;
	behaviourMap[static_cast<size_t>(EnemyBehaviourType::AGGRESSIVE)] = std::make_unique<AggressiveBehaviour>();
	behaviourMap[static_cast<size_t>(EnemyBehaviourType::COWARD)] = std::make_unique<CowardBehaviour>();
}

const EnemyBehaviour* EnemeyBehaviourMap::getBehaviour(EnemyBehaviourType type) const
{	
	return behaviourMap[static_cast<size_t>(type)].get();
}
