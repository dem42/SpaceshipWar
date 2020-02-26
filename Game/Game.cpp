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
#include "Systems/ShotReclaimSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/DamageResolutionSystem.h"
#include "Systems/HyperdriveSystem.h"
#include "Systems/RoundEndSystem.h"

Game::Game() : randomnessSource(std::make_shared<RandomnessSource>()), graphics(), inputManager(), 
	levelGenerator(randomnessSource), systems(), deltaTime(0.0f), level(1), stopRound(false)
{
	systems.push_back(new RoundEndSystem(*this));
	systems.push_back(new TextureLoadingSystem(graphics));	
	systems.push_back(new InputHandlingSystem());
	systems.push_back(new AISystem());
	systems.push_back(new VelocityUpdateSystem());	
	systems.push_back(new ShootingSystem());
	systems.push_back(new HyperdriveSystem(randomnessSource));
	systems.push_back(new MovementSystem());
	systems.push_back(new DamageSystem());
	systems.push_back(new DamageResolutionSystem());
	systems.push_back(new ShotReclaimSystem());
}

Game::~Game() 
{
	for (auto system : systems) {
		delete system;
	}
}

void Game::loop()
{	
	if (!graphics.isInitialized()) {
		std::cerr << "Graphics failed to initialize. Check stderr output for errors." << std::endl;
		return;
	}

	while (!inputManager.isCloseRequested()) {		
		Scene scene = levelGenerator.generateLevelScene(level);
		playRound(scene);
	}
}

void Game::playRound(Scene& scene)
{
	stopRound = false;
	while (!inputManager.isCloseRequested() && !stopRound) {
		updateDeltaTime();
		update(scene);		
	}
}

void Game::advanceRound(bool wasWin)
{
	if (wasWin) {
		std::cout << "won level " << level << std::endl;
		level++;
	}
	else {
		level = 1;
	}
	stopRound = true;
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
	
	graphics.render(scene);
}