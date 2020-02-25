#pragma once

#include "Engine/System.h"

class ShootingSystem : public System {
public:
	void update(float dt, Scene& scene) override;
};