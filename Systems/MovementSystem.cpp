#include "Systems/MovementSystem.h"

#include <algorithm>
#include <iostream>
#include <cmath>

#include "Engine/Utils.h"
#include "Game/Constants.h"
#include "Components/PositionComponent.h"

void MovementSystem::update(float dt, Scene& scene)
{
	for (const auto& velocity : scene.velocities) {
		if (scene.positions.hasComponent(velocity.getEntity())) {
			PositionComponent& positionCompo = scene.positions.getComponent(velocity.getEntity());
			
			// the screen origin is in top left corner
			float targetYaw = static_cast<float>(std::atan2(-velocity.y, velocity.x) *  RAD_TO_DEG);
			// our images coord system starts with x pointing up -> 90 rot counter clockwise						
			targetYaw -= 90;
									
			positionCompo.x += velocity.x * dt + velocity.anomalyPullX * dt;
			positionCompo.y += velocity.y * dt + velocity.anomalyPullY * dt;
			if (positionCompo.getEntity().hasComponent(ComponentType::PLAYER) || positionCompo.getEntity().hasComponent(ComponentType::ENEMY)) {
				positionCompo.x = clampToScreenX(positionCompo.x);
				positionCompo.y = clampToScreenY(positionCompo.y);
			}
			positionCompo.yaw = targetYaw;
		}	
	}
}
