#pragma once

#include "Engine/System.h"

class DamageSystem : public System {
public:
	void update(float dt, Scene& scene) override;
};