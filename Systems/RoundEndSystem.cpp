#include "Systems/RoundEndSystem.h"

#include "Game/Game.h"

RoundEndSystem::RoundEndSystem(Game& game) : game(game)
{
}

void RoundEndSystem::update(float dt, Scene& scene)
{
	if (victoryLap) {
		victoryLapTimer += dt;
		if (victoryLapTimer >= SpaceWarConstants::VICTORY_LAP_DURATION) {
			victoryLapTimer = 0.f;
			victoryLap = false;
			game.advanceRound(true);			
		}
		return;
	}

	int enemyCount = 0;
	for (const auto& enemy : scene.enemies) {
		enemyCount += enemy.active ? 1 : 0;
	}

	if (enemyCount == 0) {
		victoryLap = true;
	}
}
