#pragma once

#include "Engine/System.h"

class InputHandlingSystem : public System {
public:
	void update(float dt, Scene& scene) override;
};