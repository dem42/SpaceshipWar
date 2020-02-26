#include "Systems/ShotReclaimSystem.h"

#include <iostream>

void ShotReclaimSystem::update(float dt, Scene& scene)
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
