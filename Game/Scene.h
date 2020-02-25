#pragma once

#include <initializer_list>
#include <vector>

#include "Engine/ComponentContainer.h"
#include "Engine/Entity.h"

#include "Components/PositionComponent.h"
#include "Components/HeadingComponent.h"
#include "Components/ViewComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/VelocityComponent.h"

#include "Components/EnemyComponent.h"
#include "Components/ShotComponent.h"

class Scene {
public:
	Scene() = default;
		
	Entity createEntity(const std::string& name);
	void createPoolOfShotEntities(int poolSize);

	std::vector<Entity> entities;
	ComponentContainer<PositionComponent, ComponentType::POSITION> positions;
	ComponentContainer<HeadingComponent, ComponentType::HEADING> headings;
	ComponentContainer<VelocityComponent, ComponentType::VELOCITY> velocities;

	ComponentContainer<ViewComponent, ComponentType::VIEW> views;

	ComponentContainer<PlayerComponent, ComponentType::PLAYER> players;
	ComponentContainer<EnemyComponent, ComponentType::ENEMY> enemies;	

	ComponentContainer<ShotComponent, ComponentType::SHOT> shots;

private:
	long entityIdGen = 0;
};
