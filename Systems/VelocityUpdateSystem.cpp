#include "Systems/VelocityUpdateSystem.h"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "Game/Constants.h"

void VelocityUpdateSystem::update(float dt, Scene& scene)
{
	const float MINIMUM_IMPULSE = 0.001f;

	for (auto& velocityComp : scene.velocities) {
		if (!scene.headings.hasComponent(velocityComp.getEntity()) || !scene.positions.hasComponent(velocityComp.getEntity())) {
			continue;
		}

		const auto& heading = scene.headings.getComponent(velocityComp.getEntity());
		const auto& position = scene.positions.getComponent(velocityComp.getEntity());

		float impulseDx = heading.xHeading - position.x;
		float impulseDy = heading.yHeading - position.y;
		float impulseMagnitude = std::sqrt(impulseDx * impulseDx + impulseDy * impulseDy);

		if (impulseMagnitude < MINIMUM_IMPULSE) {
			continue;
		}
		
		float limitedImpulseMag = std::min(impulseMagnitude, SpaceWarConstants::MAX_IMPULSE);

		velocityComp.x = velocityComp.x + impulseDx * (limitedImpulseMag / impulseMagnitude);
		velocityComp.y = velocityComp.y + impulseDy * (limitedImpulseMag / impulseMagnitude);
		velocityComp.magnitude = std::sqrt(velocityComp.x * velocityComp.x + velocityComp.y * velocityComp.y);

		float velocityScale = std::min(SpaceWarConstants::MAX_SHIP_SPEED, velocityComp.magnitude) / velocityComp.magnitude;
		velocityComp.x *= velocityScale;
		velocityComp.y *= velocityScale;		
	}
}
