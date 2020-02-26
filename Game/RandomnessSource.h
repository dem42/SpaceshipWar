#pragma once

#include <random>
#include "Game/AI/EnemyBehaviourType.h"

class RandomnessSource {
public:
	RandomnessSource();
	
	EnemyBehaviourType sampleRandomEnemyBehaviour();
	float sampleRandomScreenXPos();
	float sampleRandomScreenYPos();
	float sampleRandomYaw();

	std::mt19937 merse;

private:
	int levelGenSeed = 0xface;
	
	std::uniform_int_distribution<int> randomScreenXPos;
	std::uniform_int_distribution<int> randomScreenYPos;
	std::uniform_int_distribution<int> randomYaw;
	std::uniform_int_distribution<std::size_t> randomEnemyBehaviour;
};