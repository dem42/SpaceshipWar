#include "Components/TestComponent.h"

TestComponent::TestComponent(const Entity& entity, const std::string & a, int b) : Component(entity), a(a), b(b)
{
}
