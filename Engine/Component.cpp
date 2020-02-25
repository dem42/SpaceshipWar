#include "Component.h"

Component::Component(ComponentType type, const std::shared_ptr<Entity>& entity) : type(type), entity(entity)
{
}

Entity& Component::getEntity()
{
	return *entity;
}

const Entity& Component::getEntity() const
{
	return *entity;
}

ComponentType Component::getType() const
{
	return type;
}
