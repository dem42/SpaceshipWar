#include "Game/Game.h"

#include <chrono>
#include <iostream>

#include "Engine/System.h"
#include "Game/Graphics.h"
#include "Game/Scene.h"

#include "Systems/AISystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/TextureLoadingSystem.h"
#include "Systems/InputHandlingSystem.h"
#include "Systems/VelocityUpdateSystem.h"
#include "Systems/ShootingSystem.h"

Game::Game() : graphics(), inputManager(), levelGenerator(), systems(), deltaTime(0.0f) 
{
	systems.push_back(new TextureLoadingSystem(graphics));
	systems.push_back(new InputHandlingSystem());
	systems.push_back(new AISystem());
	systems.push_back(new VelocityUpdateSystem());	
	systems.push_back(new ShootingSystem());
	systems.push_back(new MovementSystem());
}

Game::~Game() 
{
	for (auto system : systems) {
		delete system;
	}
}

void Game::loop()
{
	Scene scene = levelGenerator.generateLevelScene(15);

	while (!inputManager.isCloseRequested()) {
		updateDeltaTime();
		update(scene);
	}
}

void Game::updateDeltaTime()
{
	using namespace std;

	static auto time = chrono::system_clock::now();
	auto newTime = chrono::system_clock::now();
	auto diff = chrono::duration_cast<chrono::milliseconds>(newTime - time);
	deltaTime = static_cast<float>(diff.count()) / 1000.0f;
	time = newTime;
}

void Game::update(Scene& scene)
{	
	inputManager.update(scene);

	for (auto system : systems) {
		system->update(deltaTime, scene);
	}
	
	if (graphics.isInitialized()) {
		graphics.render(scene);
	}
}