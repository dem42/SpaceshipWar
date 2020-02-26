#include "Game/RandomnessSource.h"

#include "Game/Constants.h"
#include "Game/AI/EnemyBehaviourType.h"

RandomnessSource::RandomnessSource() : merse(), randomScreenXPos(0, SpaceWarConstants::SCREEN_WIDTH), randomScreenYPos(0, SpaceWarConstants::SCREEN_HEIGHT), randomYaw(0, 359), randomEnemyBehaviour(0, static_cast<std::size_t>(EnemyBehaviourType::_Count) - 1)
{
	merse.seed(levelGenSeed);
}

EnemyBehaviourType RandomnessSource::sampleRandomEnemyBehaviour()
{
	return static_cast<EnemyBehaviourType>(randomEnemyBehaviour(merse));
}

float RandomnessSource::sampleRandomScreenXPos()
{
	return static_cast<float>(randomScreenXPos(merse));
}

float RandomnessSource::sampleRandomScreenYPos()
{
	return static_cast<float>(randomScreenYPos(merse));
}

float RandomnessSource::sampleRandomYaw()
{
	return static_cast<float>(randomYaw(merse));
}
