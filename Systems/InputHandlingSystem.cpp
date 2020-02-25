#include "Systems/InputHandlingSystem.h"

void InputHandlingSystem::update(float dt, Scene& scene)
{
	for (auto& headingCompo : scene.headings) {			
		if (scene.players.hasComponent(headingCompo.getParentEntity())) {
			PlayerComponent& playerInputCompo = scene.players.getComponent(headingCompo.getParentEntity());

			headingCompo.xHeading = playerInputCompo.lastMouseX;
			headingCompo.yHeading = playerInputCompo.lastMouseY;
		}
	}
}
