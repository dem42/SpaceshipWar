#include "Game/LevelGenerator.h"

#include "Game/Constants.h"
#include <sstream>

LevelGenerator::LevelGenerator() : merse(), randomScreenXPos(0, SpaceWarConstants::SCREEN_WIDTH), randomScreenYPos(0, SpaceWarConstants::SCREEN_HEIGHT), randomYaw(0, 359), randomEnemyBehaviour(0, static_cast<std::size_t>(EnemyBehaviourType::_Count)-1)
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
	scene.players.addComponent(PlayerComponent{ playerEntity, SpaceWarConstants::PLAYER_1_ID });
	scene.positions.addComponent(PositionComponent{ playerEntity, 800, 800, 0 });
	scene.headings.addComponent(HeadingComponent{ playerEntity });
	scene.velocities.addComponent(VelocityComponent{ playerEntity });
	scene.views.addComponent(ViewComponent{ playerEntity, TextureKey{"images/spaceship.png"}, 50, 50, -45, true });

	scene.playerEntity = playerEntity;
}

void LevelGenerator::addEnemy(Scene& scene, int num)
{
	std::stringstream strbuf;
	strbuf << "Enemy " << num;
	auto enemyEntity = scene.createEntity(strbuf.str());

	scene.enemies.addComponent(EnemyComponent{ enemyEntity, static_cast<EnemyBehaviourType>(randomEnemyBehaviour(merse)) });
	scene.positions.addComponent(PositionComponent{ enemyEntity, static_cast<float>(randomScreenXPos(merse)), static_cast<float>(randomScreenYPos(merse)), static_cast<float>(randomYaw(merse)) });
	scene.headings.addComponent(HeadingComponent{ enemyEntity });
	scene.velocities.addComponent(VelocityComponent{ enemyEntity });
	scene.views.addComponent(ViewComponent{ enemyEntity, TextureKey{"images/enemy.png"}, 50, 50, -45, true });
}

void LevelGenerator::addAnomaly(Scene& scene, int num)
{
	std::stringstream strbuf;
	strbuf << "Anomaly " << num;
	auto anomalyEntity = scene.createEntity(strbuf.str());

	scene.positions.addComponent(PositionComponent{ anomalyEntity, static_cast<float>(randomScreenXPos(merse)), static_cast<float>(randomScreenYPos(merse)), 0 });
	scene.views.addComponent(ViewComponent{ anomalyEntity, TextureKey{"images/anomaly.png"}, 100, 100, -45, true });
}
