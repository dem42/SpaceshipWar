#pragma once

#include "Engine/Component.h"

class PlayerComponent : public Component {
public:
	PlayerComponent(const std::shared_ptr<Entity>& entity, const std::string& playerName) : Component(ComponentType::PLAYER, entity), playerName(playerName) {}

	std::string playerName;

	float timeUntilNextShotCanBeFired = 0;

	bool holdingLeftMouse = false;
	bool pressedRightMouse = false;
	
	bool hasStreeringInput = false;
	float lastMouseX = 0;
	float lastMouseY = 0;
};

