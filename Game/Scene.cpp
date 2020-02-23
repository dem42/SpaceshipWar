#include "Scene.h"


Entity Scene::createEntity(const std::string& name)
{
	Entity entity(name, entityIdGen++);
	return entity;
}

template <>
bool Scene::hasComponent<PositionComponent>(const Entity& entity) const
{
	return positions.hasComponent(entity);
}

template <>
PositionComponent& Scene::getComponent<PositionComponent>(const Entity& entity)
{
	return positions.getComponent(entity);
}

template <>
void Scene::addComponent<PositionComponent>(const Entity& entity, const PositionComponent& component)
{
	positions.addComponent(entity, component);
}