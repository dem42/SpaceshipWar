#pragma once

#include "Engine/Entity.h"

class Component {
public:
	Component(ComponentType type, const Entity& entity);
	const Entity& getParentEntity() const;
	ComponentType getType() const;

private:
	ComponentType type;
	Entity entity;
};