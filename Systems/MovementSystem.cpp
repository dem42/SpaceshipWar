#include "Systems/MovementSystem.h"

#include "Components/PositionComponent.h"

void MovementSystem::update(float dt, Scene& scene)
{
	for (auto& entity : scene.entities) {
		if (scene.hasComponent<PositionComponent>(entity)) {
			auto& posComp = scene.getComponent<PositionComponent>(entity);
			posComp.x += dt * 20;
			posComp.y += dt * 20;
		}
	}
}
