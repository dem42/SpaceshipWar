#include "Systems/InputHandlingSystem.h"

void InputHandlingSystem::update(float dt, Scene& scene)
{
	for (auto& player : scene.players) {
		if (!player.active) {
			continue;
		}
		if (scene.headings.hasComponent(player.getEntity())) {
			auto& heading = scene.headings.getComponent(player.getEntity());

			heading.xHeading = player.lastMouseX;
			heading.yHeading = player.lastMouseY;
		}

		if (player.pressedRightMouse) {
			if (player.hyperdriveReady) {
				player.hyperdriveActivated = true;
			} 
			player.pressedRightMouse = false;
		}
	}

}
