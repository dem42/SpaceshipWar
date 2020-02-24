#pragma once

#include <vector>
#include <memory>

#include "Game/Graphics.h"
#include "Game/InputManager.h"
#include "Game/ResourceManager.h"

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

	bool update(Scene& scene);

protected:
	Graphics graphics;
	InputManager inputManager;

	std::vector<System*> systems;
	float deltaTime;
};
