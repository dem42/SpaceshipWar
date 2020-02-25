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

protected:
	Graphics graphics;
	InputManager inputManager;
	LevelGenerator levelGenerator;

	std::vector<System*> systems;
	float deltaTime;

	void updateDeltaTime();
	void update(Scene& scene);
};
