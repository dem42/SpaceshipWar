#include "Systems/VelocityUpdateSystem.h"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "Game/Constants.h"

void computeAnomalyPull(VelocityComponent& velocity, const PositionComponent& position, Scene& scene)
{
	velocity.anomalyPullX = 0.0f;
	velocity.anomalyPullY = 0.0f;
	for (const auto& anomaly : scene.anomalies) {
		const auto& anomalyPos = scene.positions.getComponent(anomaly.getEntity());
		float distSqrd = PositionComponent::distanceSqrd(anomalyPos, position);

		if (distSqrd < SpaceWarConstants::ANOMALY_PULL_MAX_DIST) {
			float anomalyPullX = (anomalyPos.x - position.x);
			float anomalyPullY = (anomalyPos.y - position.y);
			float pullMag = std::sqrt(anomalyPullX*anomalyPullX + anomalyPullY * anomalyPullY);
			velocity.anomalyPullX += 50 * (anomalyPullX / pullMag);
			velocity.anomalyPullY += 50 * (anomalyPullY / pullMag);
		}
	}
}

void VelocityUpdateSystem::update(float dt, Scene& scene)
{
	const float MINIMUM_IMPULSE = 0.001f;
	const float MINIMUM_VELOCITY = 0.001f;

	for (auto& velocityComp : scene.velocities) {
		if (!scene.headings.hasComponent(velocityComp.getEntity()) || !scene.positions.hasComponent(velocityComp.getEntity())) {
			continue;
		}

		const auto& heading = scene.headings.getComponent(velocityComp.getEntity());
		const auto& position = scene.positions.getComponent(velocityComp.getEntity());

		float impulseDx = heading.xHeading - position.x;
		float impulseDy = heading.yHeading - position.y;
		float impulseMagnitude = std::sqrt(impulseDx * impulseDx + impulseDy * impulseDy);

		if (impulseMagnitude > MINIMUM_IMPULSE) {			
			float limitedImpulseMag = std::min(impulseMagnitude, SpaceWarConstants::MAX_IMPULSE);

			velocityComp.x = velocityComp.x + impulseDx * (limitedImpulseMag / impulseMagnitude);
			velocityComp.y = velocityComp.y + impulseDy * (limitedImpulseMag / impulseMagnitude);
		}		
		
		computeAnomalyPull(velocityComp, position, scene);

		velocityComp.magnitude = std::sqrt(velocityComp.x * velocityComp.x + velocityComp.y * velocityComp.y);

		if (velocityComp.magnitude > MINIMUM_VELOCITY) {
			float velocityScale = std::min(SpaceWarConstants::MAX_SHIP_SPEED, velocityComp.magnitude) / velocityComp.magnitude;
			velocityComp.x *= velocityScale;
			velocityComp.y *= velocityScale;
		}		
	}
}
