#pragma once

#include "Engine/Component.h"

class PlayerInputComponent : public Component {
public:
	PlayerInputComponent(const Entity& entity, const std::string& playerName) : Component(entity), playerName(playerName) {}

	std::string playerName;

	bool holdingLeftMouse = false;
	bool pressedRightMouse = false;
	
	bool hasStreeringInput = false;
	float lastMouseX = 0;
	float lastMouseY = 0;
};

