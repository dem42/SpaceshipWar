#include "Systems/HyperdriveSystem.h"

void HyperdriveSystem::update(float dt, Scene& scene)
{
	for (auto& player : scene.players) {

		if (player.hyperdriveReady) {
			if (player.pressedRightMouse) {
				player.hyperdriveReady = false;
			}
		}
		else {
			player.hyperdriveCharge += dt;

			if (player.hyperdriveCharge >= SpaceWarConstants::HYPERDRIVE_TIMER) {
				player.hyperdriveCharge = 0.f;
				player.hyperdriveReady = true;
			}
			else {
				player.hyperdriveReady = false;
			}
		}
	}

}
