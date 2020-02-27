#pragma once

#include "Engine/Component.h"

class AnomalyComponent : public Component {
public:
	AnomalyComponent(const std::shared_ptr<Entity>& entity) : Component(ComponentType::ANOMALY, entity) {}
};

