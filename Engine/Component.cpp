#include "Component.h"

Component::Component(ComponentType type, const Entity& entity) : type(type), entity(entity)
{
}

const Entity& Component::getParentEntity() const
{
	return entity;
}

ComponentType Component::getType() const
{
	return type;
}
