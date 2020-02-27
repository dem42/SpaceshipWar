#include "EnemyComponent.h"

bool EnemyComponent::isReadyToReact(float dt, float reactDeadline)
{
	timeUntilReact += dt;
	if (timeUntilReact >= reactDeadline) {
		timeUntilReact -= reactDeadline;
		return true;
	}
	return false;
}
