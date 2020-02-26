#pragma once

#include <string>

namespace SpaceWarConstants {

	const std::string PLAYER_1_ID = "player1";
	const int FPS = 60;
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 1000;

	const int MARGIN_X = 40;
	const int MARGIN_Y = 40;

	const float MAX_SHIP_SPEED = 100.0f;
	const float MAX_IMPULSE = 10.0f;
	const float TORPEDO_SPEED = 1000.f;

	const float TORPEDO_ACTIVAION_DIST_SQRD = 50.0;
	const int TORPEDO_DAMAGE = 1;

	const float HYPERDRIVE_TIMER = 5.0f;
	const float VICTORY_LAP_DURATION = 1.0f;
}
