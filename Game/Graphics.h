#pragma once

#include <vector>
#include "Game/ResourceManager.h"

struct SDL_Window;
struct SDL_Renderer;

class Scene;
class ViewComponent;

class Graphics {
public:
	Graphics();
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics(const Graphics&&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics& operator=(const Graphics&&) = delete;

	void render(Scene& scene);
	bool isInitialized() const;
	SDL_Renderer* getRenderer();
	ResourceManager& getResourceManager();

private:
	ResourceManager resourceManager;
	bool hasError;
	SDL_Window* win;
	SDL_Renderer* rend;
	std::vector<ViewComponent> sortedViews;
};