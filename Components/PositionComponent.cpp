#include "PositionComponent.h"

#include <cmath>

float PositionComponent::distanceSqrd(const PositionComponent & left, const PositionComponent & right)
{
	float dx = left.x - right.x;
	float dy = left.y - right.y;
	return dx*dx + dy*dy;
}

float PositionComponent::distance(const PositionComponent & left, const PositionComponent & right)
{
	return std::sqrt(PositionComponent::distanceSqrd(left, right));
}
