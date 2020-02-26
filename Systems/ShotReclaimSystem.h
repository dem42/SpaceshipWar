#pragma once

#include "Engine/System.h"

class ShotReclaimSystem : public System {
public:
	void update(float dt, Scene& scene) override;

private:
	float timeSinceReclaim = 0.0f;	
};