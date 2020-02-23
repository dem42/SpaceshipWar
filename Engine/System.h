#pragma once

#include "Game/Scene.h"

class System {
public:
	virtual ~System() {};
	virtual void update(float dt, Scene& scene) = 0;
};