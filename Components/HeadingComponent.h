#pragma once

#include "Engine/Component.h"

class HeadingComponent : public Component {
public:
	HeadingComponent(const Entity& entity) : Component(ComponentType::HEADING, entity) {}

	float xHeading;
	float yHeading;
};

