#include "Engine/Entity.h"

Entity::Entity(const std::string& name, long id) : name(name), id(id)
{
}

std::string Entity::getName() const
{
	return name;
}

long Entity::getId() const
{
	return id;
}
