#include "Systems/ShootingSystem.h"

void ShootingSystem::update(float dt, Scene& scene)
{
	const float SHOOTING_TIMEOUT_SEC = 0.5f;

	for (auto& player : scene.players) {
		if (player.holdingLeftMouse && player.timeUntilNextShotCanBeFired <= 0) {
			player.timeUntilNextShotCanBeFired = SHOOTING_TIMEOUT_SEC;

			for (auto& shot : scene.shots) {
				if (shot.available) {
					shot.available = false;
					shot.firedByPlayer = true;

					auto& shotVelocity = scene.velocities.getComponent(shot.getParentEntity());
					auto& playerVelocity = scene.velocities.getComponent(player.getParentEntity());

					auto& shotPosition = scene.positions.getComponent(shot.getParentEntity());
					auto& playerPosition = scene.positions.getComponent(player.getParentEntity());

					shotPosition = playerPosition;
					shotVelocity = playerVelocity;
					shotVelocity.x += 50;
					shotVelocity.y += 50;
					shotVelocity.magnitude *= 50;

					auto& shotView = scene.views.getComponent(shot.getParentEntity());
					shotView.visible = true;

					break;
				}
			}
		}
	}

	for (auto& enemy : scene.enemies) {

	}
}
