#include "Game/Graphics.h"

#include <iostream>
#include <SDL.h>

#include "Game/Scene.h"
#include "Game/Constants.h"

Graphics::Graphics() : hasError(false), win(nullptr), rend(nullptr)
{	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		hasError = true;
		std::cerr << "error initializing SDL: " << SDL_GetError() << std::endl;
	}

	win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SpaceWarConstants::SCREEN_WIDTH, SpaceWarConstants::SCREEN_HEIGHT, 0);

	// triggers the program that controls 
	// your graphics hardware and sets flags 
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	rend = SDL_CreateRenderer(win, -1, render_flags);
}

Graphics::~Graphics()
{	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
}

void Graphics::render(Scene& scene)
{	
	SDL_RenderClear(rend);

	for (const auto& view : scene.views) {
		auto& viewComponent = view.second;
		if (scene.positions.hasComponent(viewComponent.getParentEntity())) {
			auto& positionComponent = scene.positions.getComponent(viewComponent.getParentEntity());

			SDL_Rect screenRect = { static_cast<int>(positionComponent.x), static_cast<int>(positionComponent.y), viewComponent.width, viewComponent.height };
			SDL_RenderCopy(rend, resourceManager.getTexture(viewComponent.textureKey), NULL, &screenRect);
		}
	}
		
	SDL_RenderPresent(rend);	
	SDL_Delay(1000 / SpaceWarConstants::FPS);
}

bool Graphics::isInitialized() const
{
	return !hasError && win != nullptr && rend != nullptr;
}

SDL_Renderer* Graphics::getRenderer()
{
	return rend;
}

ResourceManager& Graphics::getResourceManager()
{
	return resourceManager;
}
