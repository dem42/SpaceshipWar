#pragma once

#include <memory>

#include "Engine/System.h"

class RandomnessSource;
class PlayerComponent;

class HyperdriveSystem : public System {
public:
	HyperdriveSystem(const std::shared_ptr<RandomnessSource>& rand);
	void update(float dt, Scene& scene) override;
private:
	std::shared_ptr<RandomnessSource> rand;

	void hyperdriveJump(PlayerComponent& player, Scene& scene);	
};