#pragma once

#include "Engine/System.h"

#include "Game/Constants.h"

class HyperdriveSystem : public System {
public:
	void update(float dt, Scene& scene) override;
};