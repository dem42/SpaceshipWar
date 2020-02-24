#pragma once

#include <initializer_list>
#include <vector>

#include "Engine/ComponentContainer.h"
#include "Engine/Entity.h"

#include "Components/PositionComponent.h"
#include "Components/HeadingComponent.h"
#include "Components/ViewComponent.h"
#include "Components/PlayerInputComponent.h"

class Scene {
public:
	Scene() = default;
		
	Entity createEntity(const std::string& name);

	std::vector<Entity> entities;
	ComponentContainer<PositionComponent> positions;
	ComponentContainer<HeadingComponent> headings;
	ComponentContainer<ViewComponent> views;
	ComponentContainer<PlayerInputComponent> playerInputs;

private:
	long entityIdGen = 0;
};
