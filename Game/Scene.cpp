#include "Scene.h"

#include <sstream>

Entity Scene::createEntity(const std::string& name)
{
	Entity entity(name, entityIdGen++);
	return entity;
}

void Scene::createPoolOfShotEntities(int poolSize)
{
	for (int i = 0; i < poolSize; i++) {

		std::stringstream strbuf;
		strbuf << "Shot " << i;
		auto torpedoEntity = createEntity(strbuf.str());
				
		shots.addComponent(torpedoEntity, ShotComponent{ torpedoEntity });
		headings.addComponent(torpedoEntity, HeadingComponent{ torpedoEntity });
		velocities.addComponent(torpedoEntity, VelocityComponent{ torpedoEntity });
		positions.addComponent(torpedoEntity, PositionComponent{ torpedoEntity, 0, 0, 0 });
		views.addComponent(torpedoEntity, ViewComponent{ torpedoEntity, TextureKey{"images/torpedo.png"}, 100, 100, -90, false });
	}
}
