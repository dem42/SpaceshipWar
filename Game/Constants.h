#pragma once

#include <string>

namespace SpaceWarConstants {
	const std::string PLAYER_1_ID = "player1";
	const int PLAYER_HP = 5;

	const int FPS = 60;
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 1000;

	const int MARGIN_X = 40;
	const int MARGIN_Y = 40;

	const float MAX_SHIP_SPEED = 100.0f;
	const float MAX_IMPULSE = 10.0f;
	const float TORPEDO_SPEED = 1000.f;

	const float EXPLOSION_VISIBLE_TIME = 0.2f;

	const float TORPEDO_ENEMY_ACTIVAION_DIST_SQRD = 275.0f;
	const float TORPEDO_PLAYER_ACTIVAION_DIST_SQRD = 175.0f;
	const int TORPEDO_DAMAGE = 1;

	const float HYPERDRIVE_TIMER = 10.0f;
	const float VICTORY_LAP_DURATION = 1.0f;
	
	const std::string HYPERDRIVE_LABEL = "Hyperdrive(right-click): ";
	const std::string HP_LABEL = "HP: ";

	const float ANOMALY_PULL_MAX_DIST = 5200.0f;
}

namespace SpaceWarTextures {
	const std::string PLAYER = "res/tex/spaceship.png";
	const std::string ENEMY = "res/tex/enemy.png";
	const std::string ANOMALY = "res/tex/anomaly.png";
	const std::string TORPEDO = "res/tex/torpedo_orange.png";
	const std::string EXPLOSION_SMALL = "res/tex/boom_small_sm.png";
	const std::string EXPLOSION_BIG = "res/tex/boom_big_sm.png";
	const std::string BACKGROUND = "res/tex/background1000.jpg";
}

namespace SpaceWarZ {	
	const int EXPLOSION_LAYER = 0; // closest to camera
	const int PLAYER_LAYER = 1; 
	const int ENEMY_LAYER = 10;
	const int TORPEDO_LAYER = 100;	
	const int ANOMALY_LAYER = 1000;
	const int BACKGROUND = 2000;
}
