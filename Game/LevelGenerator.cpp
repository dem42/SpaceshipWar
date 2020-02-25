#include "Game/LevelGenerator.h"

#include "Game/Constants.h"
#include <sstream>

LevelGenerator::LevelGenerator() : merse(), randomScreenXPos(0, SpaceWarConstants::SCREEN_WIDTH), randomScreenYPos(0, SpaceWarConstants::SCREEN_HEIGHT), randomYaw(0, 359)
{
	merse.seed(levelGenSeed);
}

Scene LevelGenerator::generateLevelScene(int level)
{
	const int MAX_SHOTS_PER_ACTOR = 5;

	Scene newScene;

	std::uniform_int_distribution<uint32_t> distEnem(1, level);
	std::uniform_int_distribution<uint32_t> distAnomaly(0, level / 2);
	
	int numEnemies = distEnem(merse);
	int numAnomaly = distAnomaly(merse);

	addPlayer(newScene);

	for (int i = 0; i < numEnemies; ++i) {
		addEnemy(newScene, i);
	}

	for (int i = 0; i < numAnomaly; ++i) {
		addAnomaly(newScene, i);
	}

	newScene.createPoolOfShotEntities((1 + numEnemies) * MAX_SHOTS_PER_ACTOR);

	return newScene;
}

void LevelGenerator::addPlayer(Scene& scene)
{
	auto playerEntity = scene.createEntity("PlayerEntity");
	scene.players.addComponent(playerEntity, PlayerComponent{ playerEntity, SpaceWarConstants::PLAYER_1_ID });
	scene.positions.addComponent(playerEntity, PositionComponent{ playerEntity, 800, 800, 0 });
	scene.headings.addComponent(playerEntity, HeadingComponent{ playerEntity });
	scene.velocities.addComponent(playerEntity, VelocityComponent{ playerEntity });
	scene.views.addComponent(playerEntity, ViewComponent{ playerEntity, TextureKey{"images/spaceship.png"}, 100, 100, -45, true });
}

void LevelGenerator::addEnemy(Scene& scene, int num)
{
	std::stringstream strbuf;
	strbuf << "Enemy " << num;
	auto enemyEntity = scene.createEntity(strbuf.str());

	scene.enemies.addComponent(enemyEntity, EnemyComponent{ enemyEntity });
	scene.positions.addComponent(enemyEntity, PositionComponent{ enemyEntity, static_cast<float>(randomScreenXPos(merse)), static_cast<float>(randomScreenYPos(merse)), static_cast<float>(randomYaw(merse)) });
	scene.headings.addComponent(enemyEntity, HeadingComponent{ enemyEntity });
	scene.velocities.addComponent(enemyEntity, VelocityComponent{ enemyEntity });
	scene.views.addComponent(enemyEntity, ViewComponent{ enemyEntity, TextureKey{"images/enemy.png"}, 100, 100, -45, true });
}

void LevelGenerator::addAnomaly(Scene& scene, int num)
{
	std::stringstream strbuf;
	strbuf << "Anomaly " << num;
	auto anomalyEntity = scene.createEntity(strbuf.str());

	scene.positions.addComponent(anomalyEntity, PositionComponent{ anomalyEntity, static_cast<float>(randomScreenXPos(merse)), static_cast<float>(randomScreenYPos(merse)), 0 });
	scene.views.addComponent(anomalyEntity, ViewComponent{ anomalyEntity, TextureKey{"images/anomaly.png"}, 100, 100, -45, true });
}
