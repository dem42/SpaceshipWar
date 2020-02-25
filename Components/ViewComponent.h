#pragma once

#include <string>

#include "Engine/Component.h"
#include "Game/ResourceManager.h"


class ViewComponent : public Component {
public:
	ViewComponent(const std::shared_ptr<Entity>& entity, const TextureKey& textureKey, int height, int width, int baseRotationDeg, bool visible)
		: Component(ComponentType::VIEW, entity), textureKey(textureKey), height(height), width(width), imageBaseRotation(baseRotationDeg), visible(visible)
	{
	}

	TextureKey textureKey;
	int height;
	int width;
	int imageBaseRotation;
	bool visible;
};
