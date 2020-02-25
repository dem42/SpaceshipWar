#include "Systems/MovementSystem.h"

#include <algorithm>
#include <iostream>
#include <cmath>

#include "Game/Constants.h"
#include "Components/PositionComponent.h"

void MovementSystem::update(float dt, Scene& scene)
{
	const float MINIMUM_APPROACH_DIST = 0.5f;
	const double RAD_TO_DEG = (180.0 / 3.141592653589793238463);

	for (const auto& velocity : scene.velocities) {
		if (scene.positions.hasComponent(velocity.getEntity())) {
			PositionComponent& positionCompo = scene.positions.getComponent(velocity.getEntity());
						
			if (std::fabs(velocity.magnitude) < MINIMUM_APPROACH_DIST) {
				continue;
			}
			
			// the screen origin is in top left corner
			float targetYaw = static_cast<float>(std::atan2(-velocity.y, velocity.x) *  RAD_TO_DEG);
			// our images coord system starts with x pointing up -> 90 rot counter clockwise						
			targetYaw -= 90;

			//float turnSpeed = std::min((targetYaw - positionCompo.yaw) * 50, 100.0f);
						
			positionCompo.x += velocity.x * dt;
			positionCompo.y += velocity.y * dt;
			positionCompo.yaw = targetYaw;
		}	
	}
}
