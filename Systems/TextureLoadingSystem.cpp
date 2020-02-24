#include "Systems/TextureLoadingSystem.h"

#include "Game/ResourceManager.h"
#include "Game/Graphics.h"

TextureLoadingSystem::TextureLoadingSystem(Graphics& graphics) : graphics(graphics)
{
}

void TextureLoadingSystem::update(float dt, Scene& scene)
{
	auto& resourceManager = graphics.getResourceManager();
	for (auto& view : scene.views) {
		if (!view.second.textureKey.loaded) {			
			resourceManager.loadTexture(graphics.getRenderer(), view.second.textureKey);
		}
	}
}
