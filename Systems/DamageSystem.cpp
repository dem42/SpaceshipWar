#include "Systems/DamageSystem.h"

#include <iostream>
#include <algorithm>

#include "Game/Constants.h"


void DamageSystem::update(float dt, Scene& scene)
{
	for (auto& shot : scene.shots) {
		if (shot.available) {
			// not fired
			continue;
		}

		const auto& shotPosition = scene.positions.getComponent(shot.getEntity());

		bool firedByPlayer = shot.firedByPlayer;

		auto isWithinShotActivationRadius = [&](const PositionComponent& position) {

			bool isPlayer = position.getEntity().hasComponent(ComponentType::PLAYER);
			bool isEnemy = position.getEntity().hasComponent(ComponentType::ENEMY);
			
			if (isEnemy && firedByPlayer) {
				bool isEnemyActive = scene.enemies.getComponent(position.getEntity()).active;
				return isEnemyActive && PositionComponent::distanceSqrd(shotPosition, position) < SpaceWarConstants::TORPEDO_ENEMY_ACTIVAION_DIST_SQRD;
			}
			else if (isPlayer && !firedByPlayer) {
				bool isPlayerActive = scene.players.getComponent(position.getEntity()).active;
				return isPlayerActive && PositionComponent::distanceSqrd(shotPosition, position) < SpaceWarConstants::TORPEDO_PLAYER_ACTIVAION_DIST_SQRD;
			}
			return false;
		};
		auto it = std::find_if(scene.positions.begin(), scene.positions.end(), isWithinShotActivationRadius);
		for (;it != scene.positions.end(); it = std::find_if(++it, scene.positions.end(), isWithinShotActivationRadius))
		{
			const auto& positionHit = *it;
			if (!positionHit.getEntity().hasComponent(ComponentType::HIT_POINTS)) {
				continue;
			}
			auto& hp = scene.hitPoints.getComponent(positionHit.getEntity());
			hp.damageTakenInFrame += SpaceWarConstants::TORPEDO_DAMAGE;
			shot.explode = true;
			std::cout << "Damage dealt at dist " << PositionComponent::distanceSqrd(shotPosition, positionHit) << std::endl;
		}
	}
}
