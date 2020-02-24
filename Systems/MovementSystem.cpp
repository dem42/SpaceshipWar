#include "Systems/MovementSystem.h"

#include <algorithm>
#include <iostream>
#include <cmath>

#include "Game/Constants.h"
#include "Components/PositionComponent.h"

void MovementSystem::update(float dt, Scene& scene)
{
	for (auto& heading : scene.headings) {
		HeadingComponent& headingCompo = heading.second;
		if (scene.positions.hasComponent(headingCompo.getParentEntity())) {
			PositionComponent& positionCompo = scene.positions.getComponent(headingCompo.getParentEntity());

			float dx = headingCompo.xHeading - positionCompo.x;
			float dy = headingCompo.yHeading - positionCompo.y;
			float dist = std::sqrt(dx * dx + dy * dy);
			dx /= dist;
			dy /= dist;
			
			float speed = std::min(dist, SpaceWarConstants::MAX_SHIP_SPEED);
			
			positionCompo.x += dx * speed * dt;
			positionCompo.y += dy * speed * dt;
		}	
	}
}
