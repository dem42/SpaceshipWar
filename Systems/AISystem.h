#pragma once

#include "Engine/System.h"

class AISystem : public System {
public:
	void update(float dt, Scene& scene) override;
};