#pragma once

#include "Engine/System.h"

#include "Game/Constants.h"

class Game;

class RoundEndSystem : public System {
public:
	RoundEndSystem(Game& game);
	void update(float dt, Scene& scene) override;

private:
	float victoryLapTimer = 0.0f;
	bool victoryLap = false;
	Game& game;
};