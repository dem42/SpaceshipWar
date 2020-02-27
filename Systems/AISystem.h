#pragma once

#include "Engine/System.h"

#include <memory>

class RandomnessSource;

class AISystem : public System {
public:
	AISystem(const std::shared_ptr<RandomnessSource>& rand);
	void update(float dt, Scene& scene) override;
private:
	std::shared_ptr<RandomnessSource> rand;
};