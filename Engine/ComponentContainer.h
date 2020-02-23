#pragma once

#include <unordered_map>
#include "Engine/Entity.h"

template <typename ComponentType>
class ComponentContainer {
public:
	void addComponent(const Entity& entity, const ComponentType& component);
	ComponentType& getComponent(const Entity& entity);
	bool hasComponent(const Entity& entity) const;

private:
	std::unordered_map<long, ComponentType> componentsByEntity;
};

template<typename ComponentType>
inline void ComponentContainer<ComponentType>::addComponent(const Entity& entity, const ComponentType& component)
{
	componentsByEntity.emplace(entity.getId(), component);
}

template<typename ComponentType>
inline ComponentType& ComponentContainer<ComponentType>::getComponent(const Entity& entity)
{
	return componentsByEntity.at(entity.getId());
}

template<typename ComponentType>
inline bool ComponentContainer<ComponentType>::hasComponent(const Entity& entity) const
{
	return componentsByEntity.find(entity.getId()) != componentsByEntity.end();
}