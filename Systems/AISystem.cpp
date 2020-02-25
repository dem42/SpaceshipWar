#include "Systems/AISystem.h"

#include "Game/AI/EnemyBehaviour.h"

void AISystem::update(float dt, Scene& scene)
{
	for (auto& enemy : scene.enemies) {
		auto behaviour = EnemyBehaviour::behaviourMap.getBehaviour(enemy.behaviourType);
		behaviour->act(enemy, dt, scene);
	}
}