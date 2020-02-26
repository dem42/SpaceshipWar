#include "Systems/DamageResolutionSystem.h"

void DamageResolutionSystem::update(float dt, Scene& scene)
{
	for (auto& shot : scene.shots) {
		if (shot.explode) {
			shot.available = true;
			shot.reclaimsSurvived = 0;
			shot.explode = false;

			auto& view = scene.views.getComponent(shot.getEntity());
			view.visible = false;
			view.playExplosion = true;
		}
	}

	for (auto& hp : scene.hitPoints) {
		if (hp.damageTakenInFrame > 0) {
			hp.hitPoints = (hp.hitPoints - hp.damageTakenInFrame <= 0) ? 0 : hp.hitPoints - hp.damageTakenInFrame;
			if (hp.hitPoints == 0) {
				if (hp.getEntity().hasComponent(ComponentType::ENEMY)) {
					auto& enemy = scene.enemies.getComponent(hp.getEntity());
					enemy.active = false;
				}
				else if (hp.getEntity().hasComponent(ComponentType::PLAYER)) {
					auto& player = scene.players.getComponent(hp.getEntity());
					player.active = false;
				}

				auto& view = scene.views.getComponent(hp.getEntity());
				view.visible = false;
				view.playExplosion = true;
			}
			hp.damageTakenInFrame = 0;
		}
	}
}
