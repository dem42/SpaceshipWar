#include "Component.h"

Component::Component(const Entity& entity) : entity(entity)
{
}

const Entity& Component::getParentEntity() const
{
	return entity;
}
