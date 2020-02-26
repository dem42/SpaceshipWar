#include "Game/LevelGenerator.h"

#include "Game/Constants.h"
#include "Game/RandomnessSource.h"

LevelGenerator::LevelGenerator(const std::shared_ptr<RandomnessSource>& randomnessSource) : randomnessSource(randomnessSource)
{
	
}

Scene LevelGenerator::generateLevelScene(int level)
{
	const int MAX_SHOTS_PER_ACTOR = 5;

	Scene newScene{ level };

	std::uniform_int_distribution<uint32_t> distEnem(1, level);
	std::uniform_int_distribution<uint32_t> distAnomaly(0, level / 2);
	
	int numEnemies = distEnem(randomnessSource->merse);
	int numAnomaly = distAnomaly(randomnessSource->merse);

	addPlayer(newScene);

	for (int i = 0; i < numEnemies; ++i) {
		addEnemy(newScene, i);
	}

	for (int i = 0; i < numAnomaly; ++i) {
		addAnomaly(newScene, i);
	}

	newScene.createPoolOfShotEntities((1 + numEnemies) * MAX_SHOTS_PER_ACTOR);

	addUi(newScene);

	return newScene;
}

void LevelGenerator::addUi(Scene& scene) 
{
	auto hpText = scene.createEntity("HpText");
	scene.positions.addComponent(PositionComponent{ hpText, 55, SpaceWarConstants::SCREEN_HEIGHT - 20, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ hpText, SpaceWarConstants::HP_LABEL + std::to_string(SpaceWarConstants::PLAYER_HP), true });
	scene.hpTextUiEntity = hpText;
	
	auto hyperdriveText = scene.createEntity("HyperdriveText");
	scene.positions.addComponent(PositionComponent{ hyperdriveText, SpaceWarConstants::SCREEN_WIDTH - 200, SpaceWarConstants::SCREEN_HEIGHT - 20, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ hyperdriveText, SpaceWarConstants::HYPERDRIVE_LABEL + " 0%", true });
	scene.hyperdriveUiEntity = hyperdriveText;
	
	auto levelText = scene.createEntity("LevelText");
	scene.positions.addComponent(PositionComponent{ levelText, SpaceWarConstants::SCREEN_WIDTH / 2 - 20, 20, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ levelText, "Level: " + std::to_string(scene.getLevel()), true });
	scene.levelUiEntity = levelText;
}

void LevelGenerator::addPlayer(Scene& scene)
{
	auto playerEntity = scene.createEntity("PlayerEntity");
	scene.players.addComponent(PlayerComponent{ playerEntity, SpaceWarConstants::PLAYER_1_ID });
	scene.hitPoints.addComponent(HitPointComponent{ playerEntity, SpaceWarConstants::PLAYER_HP});
	scene.positions.addComponent(PositionComponent{ playerEntity, 800, 800, 0 });
	scene.headings.addComponent(HeadingComponent{ playerEntity });
	scene.velocities.addComponent(VelocityComponent{ playerEntity });
	scene.views.addComponent(ViewComponent{ playerEntity, TextureKey{"res/tex/spaceship.png"}, 50, 50, -45, true });

	scene.playerEntity = playerEntity;
}

void LevelGenerator::addEnemy(Scene& scene, int num)
{	
	auto name = "Enemy " + std::to_string(num);
	auto enemyEntity = scene.createEntity(name);

	scene.enemies.addComponent(EnemyComponent{ enemyEntity, randomnessSource->sampleRandomEnemyBehaviour() });
	scene.hitPoints.addComponent(HitPointComponent{ enemyEntity, 1 });
	scene.positions.addComponent(PositionComponent{ enemyEntity, randomnessSource->sampleRandomScreenXPos(), randomnessSource->sampleRandomScreenYPos(), randomnessSource->sampleRandomYaw() });
	scene.headings.addComponent(HeadingComponent{ enemyEntity });
	scene.velocities.addComponent(VelocityComponent{ enemyEntity });
	scene.views.addComponent(ViewComponent{ enemyEntity, TextureKey{"res/tex/enemy.png"}, 50, 50, -45, true });
}

void LevelGenerator::addAnomaly(Scene& scene, int num)
{
	auto name = "Anomaly " + std::to_string(num);
	auto anomalyEntity = scene.createEntity(name);

	scene.positions.addComponent(PositionComponent{ anomalyEntity, randomnessSource->sampleRandomScreenXPos(), randomnessSource->sampleRandomScreenYPos(), 0 });
	scene.views.addComponent(ViewComponent{ anomalyEntity, TextureKey{"res/tex/anomaly.png"}, 100, 100, -45, true });
}
