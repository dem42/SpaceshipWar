#pragma once

#include <array>
#include <string>
#include "Engine/ComponentType.h"

class Entity {	
public:
	Entity(const std::string& name, long id);
	std::string getName() const;
	long getId() const;

	Entity(const Entity& entity) = delete;
	
	void setComponentIdx(ComponentType type, int containerIdx);
	int getComponentIdx(ComponentType type) const;
	bool hasComponent(ComponentType type) const;

private:
	std::string name;
	long id;
	std::array<int, static_cast<std::size_t>(ComponentType::_Count)> componentIdx;
};