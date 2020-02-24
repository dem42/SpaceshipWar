#pragma once

#include "Engine/System.h"

class Graphics;

class TextureLoadingSystem : public System {
public:
	TextureLoadingSystem(Graphics& graphics);
	void update(float dt, Scene& scene) override;

	TextureLoadingSystem(const TextureLoadingSystem&) = delete;
	TextureLoadingSystem& operator=(const TextureLoadingSystem&) = delete;

private:
	Graphics& graphics;
};