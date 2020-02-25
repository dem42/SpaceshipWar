#pragma once

#include "Engine/Component.h"

class HeadingComponent : public Component {
public:
	HeadingComponent(const std::shared_ptr<Entity>& entity) : Component(ComponentType::HEADING, entity) {}

	float xHeading;
	float yHeading;
};

