#pragma once

#include <vector>
#include <memory>

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
		
	std::shared_ptr<Entity> createEntity(const std::string& name);
	void createPoolOfShotEntities(int poolSize);
	ShotComponent& getShotFromPool();

	std::shared_ptr<Entity> playerEntity;
	std::vector<std::shared_ptr<Entity>> entities;
	ComponentContainer<PositionComponent, ComponentType::POSITION> positions;
	ComponentContainer<HeadingComponent, ComponentType::HEADING> headings;
	ComponentContainer<VelocityComponent, ComponentType::VELOCITY> velocities;

	ComponentContainer<ViewComponent, ComponentType::VIEW> views;

	ComponentContainer<PlayerComponent, ComponentType::PLAYER> players;
	ComponentContainer<EnemyComponent, ComponentType::ENEMY> enemies;	

	ComponentContainer<ShotComponent, ComponentType::SHOT> shots;

private:
	long entityIdGen = 0;
	std::vector<ShotComponent>::iterator shotPoolRingBufTail;
};
