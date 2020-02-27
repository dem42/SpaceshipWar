#pragma once

#include <string>

#include "Engine/Component.h"
#include "Game/ResourceManager.h"


class ViewComponent : public Component {
public:
	ViewComponent(const std::shared_ptr<Entity>& entity, const TextureKey& textureKey, int height, int width, int baseRotationDeg, int zOrder, bool visible)
		: Component(ComponentType::VIEW, entity), textureKey(textureKey), height(height), width(width), 
		zOrder(zOrder), imageBaseRotation(baseRotationDeg), visible(visible)
	{
	}

	TextureKey textureKey;
	int height;
	int width;
	int zOrder;
	int imageBaseRotation;
		
	bool visible;
};
