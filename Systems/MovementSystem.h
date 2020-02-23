#pragma once

#include "Engine/System.h"

class MovementSystem : public System {
public:
	void update(float dt, Scene& scene) override;
};