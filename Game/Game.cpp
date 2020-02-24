#include "Game/Game.h"

#include <chrono>
#include <iostream>

#include "Engine/System.h"
#include "Game/Graphics.h"
#include "Game/Scene.h"

#include "Systems/MovementSystem.h"
#include "Systems/TextureLoadingSystem.h"
#include "Systems/InputHandlingSystem.h"

Game::Game() : graphics(), inputManager(), systems(), deltaTime(0.0f) 
{
	systems.push_back(new TextureLoadingSystem(graphics));
	systems.push_back(new InputHandlingSystem());
	systems.push_back(new MovementSystem());
}

Game::~Game() 
{
	for (auto system : systems) {
		delete system;
	}
}

bool Game::update(Scene& scene) 
{	
	using namespace std;

	static auto time = chrono::system_clock::now();
	auto newTime = chrono::system_clock::now();
	auto diff = chrono::duration_cast<chrono::milliseconds>(newTime - time);
	deltaTime = static_cast<float>(diff.count()) / 1000.0f;
	time = newTime;
		
	inputManager.update(scene);

	for (auto system : systems) {
		system->update(deltaTime, scene);
	}
	
	if (graphics.isInitialized()) {
		graphics.render(scene);
	}

	return inputManager.isCloseRequested();
}