#include "PositionComponent.h"

PositionComponent::PositionComponent(const Entity& entity, float x, float y) : Component(entity), x(x), y(y)
{
}
