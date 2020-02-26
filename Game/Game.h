#pragma once

#include <vector>
#include <memory>

#include "Game/RandomnessSource.h"
#include "Game/Graphics.h"
#include "Game/InputManager.h"
#include "Game/ResourceManager.h"
#include "Game/LevelGenerator.h"

class Scene;
class System;

class Game {

public:
	Game();	
	~Game();
		
	Game(const Game&) = delete;
	Game(const Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(const Game&&) = delete;

	void loop();	
	void advanceRound(bool wasWin);

protected:
	std::shared_ptr<RandomnessSource> randomnessSource;
	Graphics graphics;
	InputManager inputManager;
	LevelGenerator levelGenerator;

	std::vector<System*> systems;
	float deltaTime;
	int level;
	bool stopRound;

	void playRound(Scene& scene);
	void updateDeltaTime();
	void update(Scene& scene);
};
