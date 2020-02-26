#include "Scene.h"

#include <sstream>

Scene::Scene(int level) : level(level), entityIdGen(0), shotPoolRingBufTail()
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
		views.addComponent(ViewComponent{ torpedoEntity, TextureKey{"res/tex/torpedo_orange.png"}, 20, 20, -90, false });
	}
	shotPoolRingBufTail = shots.begin();
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