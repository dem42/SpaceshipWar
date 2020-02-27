#pragma once

#include <array>
#include <memory>

#include "Game/AI/EnemyBehaviourType.h"

class Scene;
class EnemyBehaviour;
class EnemyComponent;
class RandomnessSource;

class EnemeyBehaviourMap {
public:
	EnemeyBehaviourMap();
	const EnemyBehaviour* getBehaviour(EnemyBehaviourType type) const;
private:
	std::array<std::unique_ptr<EnemyBehaviour>, static_cast<std::size_t>(EnemyBehaviourType::_Count)> behaviourMap;
};

class EnemyBehaviour {
public:	
	EnemyBehaviour(EnemyBehaviourType type);

	virtual void act(EnemyComponent& enemyComponent, float dt, Scene& scene, const std::shared_ptr<RandomnessSource>& rand) const = 0;
	
	EnemyBehaviourType getType() const;

	static EnemeyBehaviourMap behaviourMap;

private:
	EnemyBehaviourType type;
};