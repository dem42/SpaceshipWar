#pragma once

#include <string>

#include "Engine/Component.h"

class TestComponent : public Component {
public:
	TestComponent(const Entity& entity, const std::string& a, int b);
	
private:
	std::string a;
	int b;
};
