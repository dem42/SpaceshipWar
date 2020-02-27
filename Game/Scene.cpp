#include "Scene.h"

#include "Game/Constants.h"

Scene::Scene(int level) : level(level), entityIdGen(0), shotPoolRingBufTail(), explosionPoolRingBufTail()
{
}

int Scene::getLevel() const
{
	return level;
}

std::shared_ptr<Entity> Scene::createEntity(const std::string& name)
{
	auto newEntity = std::make_shared<Entity>(name, entityIdGen++);
	entities.emplace_back(newEntity);
	return newEntity;
}

void Scene::createPoolOfShotEntities(int poolSize)
{	
	for (int i = 0; i < poolSize; i++) {
		auto name = "Shot " + std::to_string(i);
		auto torpedoEntity = createEntity(name);
				
		shots.addComponent(ShotComponent{ torpedoEntity });
		velocities.addComponent(VelocityComponent{ torpedoEntity });
		positions.addComponent(PositionComponent{ torpedoEntity, 0, 0, 0 });
		views.addComponent(ViewComponent{ torpedoEntity, TextureKey{SpaceWarTextures::TORPEDO}, 20, 20, -90, SpaceWarZ::TORPEDO_LAYER, false });
	}
	shotPoolRingBufTail = shots.begin();
}

void Scene::createPoolOfExplosion(int poolSize)
{
	for (int i = 0; i < poolSize; i++) {
		auto name = "Explosion " + std::to_string(i);
		auto explosionEntity = createEntity(name);

		explosions.addComponent(ExplosionComponent{ explosionEntity });		
		positions.addComponent(PositionComponent{ explosionEntity, 0, 0, 0 });
		views.addComponent(ViewComponent{ explosionEntity, TextureKey{SpaceWarTextures::EXPLOSION_SMALL}, 40, 40, -90, SpaceWarZ::EXPLOSION_LAYER, false });
	}
	explosionPoolRingBufTail = explosions.begin();
}

ExplosionComponent& Scene::getExplosionFromPool()
{
	if (explosionPoolRingBufTail == explosions.end()) {
		explosionPoolRingBufTail = explosions.begin();
	}

	auto& explosionComp = *explosionPoolRingBufTail;
	explosionPoolRingBufTail++;

	return explosionComp;
}

ShotComponent& Scene::getShotFromPool()
{
	if (shotPoolRingBufTail == shots.end()) {
		shotPoolRingBufTail = shots.begin();
	}

	auto& shotComp = *shotPoolRingBufTail;
	shotPoolRingBufTail++;

	return shotComp;
}