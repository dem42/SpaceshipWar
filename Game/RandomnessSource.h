#pragma once

#include <random>
#include <tuple>
#include "Game/AI/AiParams.h"

class RandomnessSource {
public:
	RandomnessSource();
	
	AiParams sampleRandomEnemyBehaviour();
	float sampleRandomScreenXPos();
	float sampleRandomScreenYPos();
	float sampleRandomYaw();	

	std::mt19937 merse;

private:	
	std::uniform_int_distribution<int> randomScreenXPos;
	std::uniform_int_distribution<int> randomScreenYPos;
	std::uniform_int_distribution<int> randomYaw;
	std::uniform_int_distribution<std::size_t> randomEnemyBehaviour;
	std::normal_distribution<float> randomDistFactor;
	std::uniform_int_distribution<int> randomEdge;
};