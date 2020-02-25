#pragma once

#include <unordered_map>
#include "Engine/Entity.h"


template <typename T, ComponentType Type, typename Iterator = typename std::vector<T>::iterator>
class ComponentContainer {
public:
	void addComponent(Entity& entity, const T& component);
	T& getComponent(const Entity& entity);
	bool hasComponent(const Entity& entity) const;

	Iterator begin();
	Iterator end();

private:
	std::vector<T> components;
};

template<typename T, ComponentType Type, typename Iterator>
inline void ComponentContainer<T, Type, Iterator>::addComponent(Entity& entity, const T& component)
{	
	int compoIdx = static_cast<int>(components.size());
	entity.setComponentIdx(Type, compoIdx);
	components.emplace_back(component);
}

template<typename T, ComponentType Type, typename Iterator>
inline T& ComponentContainer<T, Type, Iterator>::getComponent(const Entity& entity)
{
	int compoIdx = entity.getComponentIdx(Type);
	return components.at(static_cast<std::size_t>(compoIdx));	
}

template<typename T, ComponentType Type, typename Iterator>
inline bool ComponentContainer<T, Type, Iterator>::hasComponent(const Entity& entity) const
{
	return entity.getComponentIdx(Type) != COMPONENT_NOT_PRESENT;
	//return componentsByEntity.find(entity.getId()) != componentsByEntity.end();
}

template<typename T, ComponentType Type, typename Iterator>
inline Iterator ComponentContainer<T, Type, Iterator>::begin()
{
	return components.begin();
}

template<typename T, ComponentType Type, typename Iterator>
inline Iterator ComponentContainer<T, Type, Iterator>::end()
{
	return components.end();
}

/////////////////////////////////////////////
// Map
/////////////////////////////////////////////
template <typename ComponentType, typename Iterator = typename std::unordered_map<long, ComponentType>::iterator>
class MapComponentContainer {
public:
	void addComponent(Entity& entity, const ComponentType& component);
	ComponentType& getComponent(const Entity& entity);
	bool hasComponent(const Entity& entity) const;

	Iterator begin();
	Iterator end();

private:
	std::unordered_map<long, ComponentType> componentsByEntity;
};

template<typename ComponentType, typename Iterator>
inline void MapComponentContainer<ComponentType, Iterator>::addComponent(Entity& entity, const ComponentType& component)
{
	componentsByEntity.emplace(entity.getId(), component);
}

template<typename ComponentType, typename Iterator>
inline ComponentType& MapComponentContainer<ComponentType, Iterator>::getComponent(const Entity& entity)
{
	return componentsByEntity.at(entity.getId());
}

template<typename ComponentType, typename Iterator>
inline bool MapComponentContainer<ComponentType, Iterator>::hasComponent(const Entity& entity) const
{
	return componentsByEntity.find(entity.getId()) != componentsByEntity.end();
}

template<typename ComponentType, typename Iterator>
inline Iterator MapComponentContainer<ComponentType, Iterator>::begin()
{
	return componentsByEntity.begin();
}

template<typename ComponentType, typename Iterator>
inline Iterator MapComponentContainer<ComponentType, Iterator>::end()
{
	return componentsByEntity.end();
}
