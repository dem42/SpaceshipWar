#include "Game/LevelGenerator.h"

#include "Game/Constants.h"
#include "Game/RandomnessSource.h"

LevelGenerator::LevelGenerator(const std::shared_ptr<RandomnessSource>& randomnessSource) : randomnessSource(randomnessSource)
{
	
}

int LevelGenerator::getHpForLevel(const Scene& scene) const
{
	return SpaceWarConstants::PLAYER_HP + scene.getLevel();
}

Scene LevelGenerator::generateLevelScene(int level) const
{
	if (level == 0) {
		return generateTutorial();
	}

	const int MAX_SHOTS_PER_ACTOR = 5;

	Scene newScene{ level };

	std::uniform_int_distribution<uint32_t> distEnem(1, level);
	std::uniform_int_distribution<uint32_t> distAnomaly(2, 2*level);
	
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
	newScene.createPoolOfExplosion(5);

	addUi(newScene);
	addBackground(newScene);

	return newScene;
}

Scene LevelGenerator::generateTutorial() const {
	Scene scene{ 0 };

	addBackground(scene);

	auto playerEntity = scene.createEntity("PlayerEntity");
	scene.players.addComponent(PlayerComponent{ playerEntity, SpaceWarConstants::PLAYER_1_ID });
	scene.hitPoints.addComponent(HitPointComponent{ playerEntity, getHpForLevel(scene) });
	scene.positions.addComponent(PositionComponent{ playerEntity, 800, 800, 0 });
	scene.velocities.addComponent(VelocityComponent{ playerEntity });
	scene.views.addComponent(ViewComponent{ playerEntity, TextureKey{SpaceWarTextures::PLAYER}, 50, 50, -45, SpaceWarZ::PLAYER_LAYER, true });

	scene.playerEntity = playerEntity;

	auto text1 = scene.createEntity("TutorialText1");
	scene.positions.addComponent(PositionComponent{ text1, 500, 200, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ text1, "Welcome to SpaceWarZ", true });

	auto text2 = scene.createEntity("TutorialText2");
	scene.positions.addComponent(PositionComponent{ text2, 500, 300, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ text2, "Eliminate all enemy spaceships! You fly your spaceship by moving the mouse.", true });

	auto text3 = scene.createEntity("TutorialText3");
	scene.positions.addComponent(PositionComponent{ text3, 500, 400, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ text3, "You can fire your gun using left click.", true });

	auto text4 = scene.createEntity("TutorialText3");
	scene.positions.addComponent(PositionComponent{ text4, 500, 500, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ text4, "Right click actives a hyperdrive that randomly teleports you somewhere.", true });

	auto text5 = scene.createEntity("TutorialText5");
	scene.positions.addComponent(PositionComponent{ text5, 500, 600, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ text5, "The hyperdrive recharges every 7 seconds.", true });

	auto text6 = scene.createEntity("TutorialText6");
	scene.positions.addComponent(PositionComponent{ text6, 500, 700, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ text6, "Press left-click to begin.", true });
	
	auto hpText = scene.createEntity("HpText");
	scene.positions.addComponent(PositionComponent{ hpText, 55, SpaceWarConstants::SCREEN_HEIGHT - 20, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ hpText, SpaceWarConstants::HP_LABEL + std::to_string(getHpForLevel(scene)), true });
	scene.hpTextUiEntity = hpText;

	auto hyperdriveText = scene.createEntity("HyperdriveText");
	scene.positions.addComponent(PositionComponent{ hyperdriveText, SpaceWarConstants::SCREEN_WIDTH - 200, SpaceWarConstants::SCREEN_HEIGHT - 20, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ hyperdriveText, SpaceWarConstants::HYPERDRIVE_LABEL + " 0%", true });
	scene.hyperdriveUiEntity = hyperdriveText;
	return scene;
}

void LevelGenerator::addBackground(Scene& scene) const
{
	auto bckEntity = scene.createEntity("Background");
	scene.positions.addComponent(PositionComponent{ bckEntity, 500, 500, 0 });
	scene.views.addComponent(ViewComponent{ bckEntity, TextureKey{SpaceWarTextures::BACKGROUND}, 1000, 1000, 0, SpaceWarZ::BACKGROUND, true });
}

void LevelGenerator::addUi(Scene& scene) const
{
	auto hpText = scene.createEntity("HpText");
	scene.positions.addComponent(PositionComponent{ hpText, 55, SpaceWarConstants::SCREEN_HEIGHT - 20, 0 });
	scene.textViews.addComponent(TextUiViewComponent{ hpText, SpaceWarConstants::HP_LABEL + std::to_string(getHpForLevel(scene)), true });
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

void LevelGenerator::addPlayer(Scene& scene) const
{
	auto playerEntity = scene.createEntity("PlayerEntity");
	scene.players.addComponent(PlayerComponent{ playerEntity, SpaceWarConstants::PLAYER_1_ID });
	scene.hitPoints.addComponent(HitPointComponent{ playerEntity, getHpForLevel(scene)});
	scene.positions.addComponent(PositionComponent{ playerEntity, 800, 800, 0 });
	scene.headings.addComponent(HeadingComponent{ playerEntity });
	scene.velocities.addComponent(VelocityComponent{ playerEntity });
	scene.views.addComponent(ViewComponent{ playerEntity, TextureKey{SpaceWarTextures::PLAYER}, 50, 50, -45, SpaceWarZ::PLAYER_LAYER, true });

	scene.playerEntity = playerEntity;
}

void LevelGenerator::addEnemy(Scene& scene, int num) const
{	
	auto name = "Enemy " + std::to_string(num);
	auto enemyEntity = scene.createEntity(name);
	
	scene.enemies.addComponent(EnemyComponent{ enemyEntity, randomnessSource->sampleRandomEnemyBehaviour() });
	scene.hitPoints.addComponent(HitPointComponent{ enemyEntity, 1 });
	scene.positions.addComponent(PositionComponent{ enemyEntity, randomnessSource->sampleRandomScreenXPos(), randomnessSource->sampleRandomScreenYPos(), randomnessSource->sampleRandomYaw() });
	scene.headings.addComponent(HeadingComponent{ enemyEntity });
	scene.velocities.addComponent(VelocityComponent{ enemyEntity });
	scene.views.addComponent(ViewComponent{ enemyEntity, TextureKey{SpaceWarTextures::ENEMY}, 50, 50, -45, SpaceWarZ::ENEMY_LAYER, true });
}

void LevelGenerator::addAnomaly(Scene& scene, int num) const
{
	auto name = "Anomaly " + std::to_string(num);
	auto anomalyEntity = scene.createEntity(name);

	scene.positions.addComponent(PositionComponent{ anomalyEntity, randomnessSource->sampleRandomScreenXPos(), randomnessSource->sampleRandomScreenYPos(), 0 });
	scene.anomalies.addComponent(AnomalyComponent{ anomalyEntity });
	scene.views.addComponent(ViewComponent{ anomalyEntity, TextureKey{SpaceWarTextures::ANOMALY}, 100, 100, -45, SpaceWarZ::ANOMALY_LAYER, true });
}
