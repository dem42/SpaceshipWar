#pragma once

#include "Engine/Component.h"

class HeadingComponent : public Component {
public:
	HeadingComponent(const Entity& entity) : Component(entity) {}

	float xHeading;
	float yHeading;
};

