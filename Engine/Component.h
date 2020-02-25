#pragma once

#include <memory>

#include "Engine/Entity.h"

class Component {
public:
	Component(ComponentType type, const std::shared_ptr<Entity>& entity);
	
	Entity& getEntity();
	const Entity& getEntity() const;

	ComponentType getType() const;

private:
	ComponentType type;
	std::shared_ptr<Entity> entity;
};