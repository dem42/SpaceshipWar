#include "Game/RandomnessSource.h"

#include "Game/Constants.h"
#include "Game/AI/AiParams.h"

RandomnessSource::RandomnessSource() : merse(), randomScreenXPos(0, SpaceWarConstants::SCREEN_WIDTH), randomScreenYPos(0, SpaceWarConstants::SCREEN_HEIGHT), 
	randomYaw(0, 359), randomEnemyBehaviour(0, static_cast<std::size_t>(EnemyBehaviourType::_Count) - 1),
	randomDistFactor(10, 7)
{
}

AiParams RandomnessSource::sampleRandomEnemyBehaviour()
{
	AiParams params;

	params.type = static_cast<EnemyBehaviourType>(randomEnemyBehaviour(merse));
	params.distanceFactor = randomDistFactor(merse);
	
	return params;
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
