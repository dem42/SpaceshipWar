#pragma once

#include "Engine/System.h"

class CleanupSystem : public System {
public:
	void update(float dt, Scene& scene) override;

private:
	float timeSinceReclaim = 0.0f;	

	void reclaimShots(float dt, Scene& scene);
	void cleanExplosions(float dt, Scene& scene);
};