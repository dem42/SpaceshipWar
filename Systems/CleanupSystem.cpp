#include "Systems/CleanupSystem.h"

#include <iostream>
#include "Game/Constants.h"

void CleanupSystem::reclaimShots(float dt, Scene& scene)
{
	const float RECLAIM_TIMEOUT = 1.0f;
	const int NUM_RECLAIM_LIMIT = 5;

	timeSinceReclaim += dt;
	if (timeSinceReclaim < RECLAIM_TIMEOUT) {
		return;
	}
	timeSinceReclaim -= RECLAIM_TIMEOUT;

	int reclaimed = 0;
	for (auto& shot : scene.shots) {
		if (shot.available) {
			continue;
		}
		if (shot.reclaimsSurvived + 1 >= NUM_RECLAIM_LIMIT) {
			shot.reclaimsSurvived = 0;
			shot.available = true;
			shot.firedByPlayer = false;
			shot.explode = false;
			auto& viewComponent = scene.views.getComponent(shot.getEntity());
			viewComponent.visible = false;
			reclaimed++;
		}
		else {
			shot.reclaimsSurvived++;
		}
	}
}

void CleanupSystem::cleanExplosions(float dt, Scene& scene)
{
	for (auto& explosion :scene.explosions) {
		if (explosion.active) {
			explosion.timeUntilHidden += dt;
			if (explosion.timeUntilHidden >= SpaceWarConstants::EXPLOSION_VISIBLE_TIME) {
				explosion.active = false;
				explosion.timeUntilHidden = 0.0f;

				auto& view = scene.views.getComponent(explosion.getEntity());
				view.visible = false;
			}
		}
	}
}

void CleanupSystem::update(float dt, Scene& scene)
{
	cleanExplosions(dt, scene);
	reclaimShots(dt, scene);
}
