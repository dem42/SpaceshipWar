#pragma once

#include <vector>
#include <memory>

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
	void playRound(Scene& scene);
	void advanceRound(bool wasWin);

protected:
	Graphics graphics;
	InputManager inputManager;
	LevelGenerator levelGenerator;

	std::vector<System*> systems;
	float deltaTime;
	int level;

	void updateDeltaTime();
	void update(Scene& scene);
};
