#pragma once

#include "Engine/Entity.h"

class Component {
public:
	Component(const Entity& entity);
	Entity& getParentEntity();

private:
	Entity entity;
};