#pragma once

#include <string>

class Entity {	
public:
	Entity(const std::string& name, long id);
	std::string getName() const;
	long getId() const;

private:
	std::string name;
	long id;
};