#pragma once

#include <vector>

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

	void update(Scene& scene);

protected:
	std::vector<System*> systems;
	float deltaTime;
};
