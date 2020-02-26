#pragma once

#include "Engine/Component.h"

class HitPointComponent : public Component {
public:
	HitPointComponent(const std::shared_ptr<Entity>& entity, int hitPoints) : Component(ComponentType::HIT_POINTS, entity), hitPoints(hitPoints), maxHitPoints(hitPoints) {}

	int damageTakenInFrame = 0;
	int hitPoints;
	int maxHitPoints;
};

