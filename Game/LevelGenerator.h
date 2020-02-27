#pragma once

#include <random>

#include "Game/Scene.h"

class RandomnessSource;

class LevelGenerator {
public:
	LevelGenerator(const std::shared_ptr<RandomnessSource>& randomnessSource);
	Scene generateLevelScene(int level) const;

private:
	std::shared_ptr<RandomnessSource> randomnessSource;

	void addPlayer(Scene& scene) const;
	void addEnemy(Scene& scene, int num) const;
	void addAnomaly(Scene& scene, int num) const;
	void addUi(Scene& scene) const;
	void addBackground(Scene& scene) const;
	int getHpForLevel(const Scene& scene) const;
	Scene generateTutorial() const;
};