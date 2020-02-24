#pragma once

#include "Engine/Entity.h"

class Component {
public:
	Component(const Entity& entity);
	const Entity& getParentEntity() const;

private:
	Entity entity;
};