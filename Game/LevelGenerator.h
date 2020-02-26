#pragma once

#include <random>

#include "Game/Scene.h"

class RandomnessSource;

class LevelGenerator {
public:
	LevelGenerator(const std::shared_ptr<RandomnessSource>& randomnessSource);
	Scene generateLevelScene(int level);

private:
	std::shared_ptr<RandomnessSource> randomnessSource;

	void addPlayer(Scene& scene);
	void addEnemy(Scene& scene, int num);
	void addAnomaly(Scene& scene, int num);
	void addUi(Scene& scene);
};