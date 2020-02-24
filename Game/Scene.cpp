#include "Scene.h"


Entity Scene::createEntity(const std::string& name)
{
	Entity entity(name, entityIdGen++);
	return entity;
}