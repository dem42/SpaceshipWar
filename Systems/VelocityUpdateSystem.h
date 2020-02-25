#pragma once

#include "Engine/System.h"

class VelocityUpdateSystem : public System {
public:
	void update(float dt, Scene& scene) override;
};