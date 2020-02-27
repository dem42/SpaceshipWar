#include "Systems/AISystem.h"

#include "Game/AI/EnemyBehaviour.h"
#include "Game/RandomnessSource.h"

AISystem::AISystem(const std::shared_ptr<RandomnessSource>& rand) : rand(rand)
{
}

void AISystem::update(float dt, Scene& scene)
{
	for (auto& enemy : scene.enemies) {
		if (!enemy.active) {
			continue;
		}
		auto behaviour = EnemyBehaviour::behaviourMap.getBehaviour(enemy.aiParams.type);
		behaviour->act(enemy, dt, scene, rand);
	}
}
