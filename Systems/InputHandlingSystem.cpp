#include "Systems/InputHandlingSystem.h"

void InputHandlingSystem::update(float dt, Scene& scene)
{
	for (auto& heading : scene.headings) {
		HeadingComponent& headingCompo = heading.second;		
		if (scene.playerInputs.hasComponent(headingCompo.getParentEntity())) {
			PlayerInputComponent& playerInputCompo = scene.playerInputs.getComponent(headingCompo.getParentEntity());

			headingCompo.xHeading = playerInputCompo.lastMouseX;
			headingCompo.yHeading = playerInputCompo.lastMouseY;
		}
	}
}
