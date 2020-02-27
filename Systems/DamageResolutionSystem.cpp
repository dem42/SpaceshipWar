#include "Systems/DamageResolutionSystem.h"

#include "Game/Constants.h"

void updateUi(const HitPointComponent& hp, Scene& scene)
{
	if (hp.getEntity().hasComponent(ComponentType::PLAYER)) {

		auto& textUi = scene.textViews.getComponent(*scene.hpTextUiEntity);
		textUi.text = SpaceWarConstants::HP_LABEL + std::to_string(hp.hitPoints);
	}	
}

void addExplosion(const Entity& entityThatExploded, Scene& scene, bool isBig)
{
	auto& explosion = scene.getExplosionFromPool();
	explosion.active = true;
	explosion.timeUntilHidden = 0.0f;
	
	const auto& posOfExplosion = scene.positions.getComponent(entityThatExploded);
	auto& posForCopy = scene.positions.getComponent(explosion.getEntity());

	posForCopy.x = posOfExplosion.x;
	posForCopy.y = posOfExplosion.y;

	auto& view = scene.views.getComponent(explosion.getEntity());
	view.visible = true;
	if (isBig) {
		view.height = 50;
		view.width = 50;
	}
	else {
		view.height = 20;
		view.width = 20;
	}
}

void DamageResolutionSystem::update(float dt, Scene& scene)
{
	for (auto& shot : scene.shots) {
		if (shot.explode) {
			shot.available = true;
			shot.reclaimsSurvived = 0;
			shot.explode = false;

			auto& view = scene.views.getComponent(shot.getEntity());
			view.visible = false;

			addExplosion(shot.getEntity(), scene, false);
		}
	}

	for (auto& hp : scene.hitPoints) {
		if (hp.damageTakenInFrame > 0) {
			hp.hitPoints = (hp.hitPoints - hp.damageTakenInFrame <= 0) ? 0 : hp.hitPoints - hp.damageTakenInFrame;
			
			updateUi(hp, scene);
			
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

				addExplosion(hp.getEntity(), scene, true);
			}
			hp.damageTakenInFrame = 0;
		}
	}
}
