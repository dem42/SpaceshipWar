#pragma once

#include <vector>
#include <memory>

#include "Engine/ComponentContainer.h"
#include "Engine/Entity.h"

#include "Components/PositionComponent.h"
#include "Components/HeadingComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/VelocityComponent.h"

#include "Components/EnemyComponent.h"
#include "Components/ShotComponent.h"
#include "Components/HitPointComponent.h"

#include "Components/ViewComponent.h"
#include "Components/TextUiViewComponent.h"

class Scene {
public:
	Scene(int level);

	int getLevel() const;
		
	std::shared_ptr<Entity> createEntity(const std::string& name);
	void createPoolOfShotEntities(int poolSize);
	ShotComponent& getShotFromPool();

	// special entities
	std::shared_ptr<Entity> playerEntity;
	std::shared_ptr<Entity> hpTextUiEntity;
	std::shared_ptr<Entity> hyperdriveUiEntity;
	std::shared_ptr<Entity> levelUiEntity;


	std::vector<std::shared_ptr<Entity>> entities;
	ComponentContainer<PositionComponent, ComponentType::POSITION> positions;
	ComponentContainer<HeadingComponent, ComponentType::HEADING> headings;
	ComponentContainer<VelocityComponent, ComponentType::VELOCITY> velocities;

	ComponentContainer<ViewComponent, ComponentType::VIEW> views;
	ComponentContainer<TextUiViewComponent, ComponentType::TEXT_UI_VIEW> textViews;

	ComponentContainer<PlayerComponent, ComponentType::PLAYER> players;
	ComponentContainer<EnemyComponent, ComponentType::ENEMY> enemies;	

	ComponentContainer<ShotComponent, ComponentType::SHOT> shots;
	ComponentContainer<HitPointComponent, ComponentType::HIT_POINTS> hitPoints;

private:
	int level;
	long entityIdGen;
	std::vector<ShotComponent>::iterator shotPoolRingBufTail;
};
