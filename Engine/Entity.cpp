#include "Engine/Entity.h"

Entity::Entity(const std::string& name, long id) : name(name), id(id), componentIdx()
{
	componentIdx.fill(COMPONENT_NOT_PRESENT);
}

std::string Entity::getName() const
{
	return name;
}

long Entity::getId() const
{
	return id;
}

void Entity::setComponentIdx(ComponentType type, int containerIdx)
{
	componentIdx[static_cast<std::size_t>(type)] = containerIdx;
}

int Entity::getComponentIdx(ComponentType type) const
{
	return componentIdx[static_cast<std::size_t>(type)];
}


bool Entity::hasComponent(ComponentType type) const
{
	return componentIdx[static_cast<std::size_t>(type)] != COMPONENT_NOT_PRESENT;
}