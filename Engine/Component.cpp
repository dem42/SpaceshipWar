#include "Component.h"

Component::Component(const Entity& entity) : entity(entity)
{
}

Entity & Component::getParentEntity()
{
	return entity;
}
