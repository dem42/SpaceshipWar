#pragma once

#include "Engine/System.h"

class DamageResolutionSystem : public System {
public:
	void update(float dt, Scene& scene) override;
};