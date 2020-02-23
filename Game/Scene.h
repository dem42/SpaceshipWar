#pragma once

#include <initializer_list>
#include <vector>

#include "Engine/ComponentContainer.h"
#include "Engine/Entity.h"

#include "Components/PositionComponent.h"

class Scene {
public:
	Scene() = default;
		
	Entity createEntity(const std::string& name);

	std::vector<Entity> entities;
	ComponentContainer<PositionComponent> positions;

	template <typename CT>
	bool hasComponent(const Entity& entity) const;

	template <typename CT>
	CT& getComponent(const Entity& entity);

	template <typename CT>
	void addComponent(const Entity& entity, const CT& component);

private:
	long entityIdGen = 0;
};