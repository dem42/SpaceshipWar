#pragma once

#include <random>

#include "Game/Scene.h"

class LevelGenerator {
public:
	LevelGenerator();
	Scene generateLevelScene(int level);

private:
	int levelGenSeed = 0xface;
	std::mt19937 merse;
	std::uniform_int_distribution<int> randomScreenXPos;
	std::uniform_int_distribution<int> randomScreenYPos;
	std::uniform_int_distribution<int> randomYaw;
	std::uniform_int_distribution<std::size_t> randomEnemyBehaviour;

	void addPlayer(Scene& scene);
	void addEnemy(Scene& scene, int num);
	void addAnomaly(Scene& scene, int num);
};