#include "Systems/ShootingSystem.h"
#include "Game/Constants.h"

void createShot(Entity& shooter, Scene& scene)
{
	auto& shot = scene.getShotFromPool();

	shot.reclaimsSurvived = 0;
	shot.available = false;
	shot.explode = false;
	shot.firedByPlayer = shooter.hasComponent(ComponentType::PLAYER);

	auto& shotVelocity = scene.velocities.getComponent(shot.getEntity());
	auto& shooterVelocity = scene.velocities.getComponent(shooter);

	shotVelocity.x = SpaceWarConstants::TORPEDO_SPEED * shooterVelocity.x / shooterVelocity.magnitude;
	shotVelocity.y = SpaceWarConstants::TORPEDO_SPEED * shooterVelocity.y / shooterVelocity.magnitude;
	shotVelocity.magnitude = SpaceWarConstants::TORPEDO_SPEED;

	auto& shotPosition = scene.positions.getComponent(shot.getEntity());
	auto& shooterPosition = scene.positions.getComponent(shooter);

	shotPosition.x = shooterPosition.x;
	shotPosition.y = shooterPosition.y;
	shotPosition.yaw = shooterPosition.yaw;

	auto& shotView = scene.views.getComponent(shot.getEntity());
	shotView.visible = true;
}

void ShootingSystem::update(float dt, Scene& scene)
{
	const float SHOOTING_TIMEOUT_SEC = 0.5f;	

	for (auto& player : scene.players) {
		if (!player.active) {
			continue;
		}
		if (player.holdingLeftMouse && player.timeUntilNextShotCanBeFired <= 0) {
			player.timeUntilNextShotCanBeFired = SHOOTING_TIMEOUT_SEC;

			createShot(player.getEntity(), scene);
		}
		else if (player.holdingLeftMouse || player.timeUntilNextShotCanBeFired > 0) {
			player.timeUntilNextShotCanBeFired -= dt;
		}
	}

	for (auto& enemy : scene.enemies) {
		if (!enemy.active) {
			continue;
		}
		if (enemy.shooting && enemy.timeUntilNextShotCanBeFired <= 0) {
			enemy.timeUntilNextShotCanBeFired = SHOOTING_TIMEOUT_SEC;

			createShot(enemy.getEntity(), scene);
		}
		else if (enemy.shooting) {
			enemy.timeUntilNextShotCanBeFired -= dt;
		}
	}
}
