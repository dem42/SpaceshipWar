#include "Game/Game.h"

#include <chrono>
#include <iostream>

#include "Engine/System.h"
#include "Game/Scene.h"
#include "Systems/MovementSystem.h"

Game::Game() : systems(), deltaTime(0.0f) 
{
	systems.push_back(new MovementSystem());
}

Game::~Game() 
{
	for (auto system : systems) {
		delete system;
	}
}

void Game::update(Scene& scene) 
{
	using namespace std;

	static auto time = chrono::system_clock::now();
	auto newTime = chrono::system_clock::now();
	auto diff = chrono::duration_cast<chrono::milliseconds>(newTime - time);
	deltaTime = static_cast<float>(diff.count()) / 1000.0f;
	time = newTime;

	cout << "Elapsed frameTime: " << deltaTime << "s" << endl;
	
	for (auto system : systems) {
		system->update(deltaTime, scene);
	}
}