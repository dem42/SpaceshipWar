#pragma once

#include <string>

#include "Engine/Component.h"
#include "Game/ResourceManager.h"


class ViewComponent : public Component {
public:
	ViewComponent(const Entity& entity, const TextureKey& textureKey, int height, int width) 
		: Component(entity), textureKey(textureKey), height(height), width(width)
	{
	}

	TextureKey textureKey;
	int height;
	int width;
};
