#pragma once

#include <unordered_map>
#include "Engine/Entity.h"

template <typename ComponentType, typename Iterator = typename std::unordered_map<long, ComponentType>::iterator>
class ComponentContainer {
public:
	void addComponent(const Entity& entity, const ComponentType& component);
	ComponentType& getComponent(const Entity& entity);
	bool hasComponent(const Entity& entity) const;

	Iterator begin();
	Iterator end();

private:
	std::unordered_map<long, ComponentType> componentsByEntity;
};

template<typename ComponentType, typename Iterator>
inline void ComponentContainer<ComponentType, Iterator>::addComponent(const Entity& entity, const ComponentType& component)
{
	componentsByEntity.emplace(entity.getId(), component);
}

template<typename ComponentType, typename Iterator>
inline ComponentType& ComponentContainer<ComponentType, Iterator>::getComponent(const Entity& entity)
{
	return componentsByEntity.at(entity.getId());
}

template<typename ComponentType, typename Iterator>
inline bool ComponentContainer<ComponentType, Iterator>::hasComponent(const Entity& entity) const
{
	return componentsByEntity.find(entity.getId()) != componentsByEntity.end();
}

template<typename ComponentType, typename Iterator>
inline Iterator ComponentContainer<ComponentType, Iterator>::begin()
{
	return componentsByEntity.begin();
}

template<typename ComponentType, typename Iterator>
inline Iterator ComponentContainer<ComponentType, Iterator>::end()
{
	return componentsByEntity.end();
}
