#include "Game/Graphics.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <tuple>

#include "Game/Scene.h"
#include "Game/Constants.h"

Graphics::Graphics() : resourceManager(), hasError(false), win(nullptr), rend(nullptr)
{	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		hasError = true;
		std::cerr << "error initializing SDL: " << SDL_GetError() << std::endl;
	}

	if (TTF_Init() != 0) {
		hasError = true;
		std::cerr << "error initializing TTF: " << TTF_GetError() << std::endl;
	}

	win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SpaceWarConstants::SCREEN_WIDTH, SpaceWarConstants::SCREEN_HEIGHT, 0);
	
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	rend = SDL_CreateRenderer(win, -1, render_flags);

	bool fontLoaded = resourceManager.loadFont("res/font/october.ttf");
	if (!fontLoaded) {
		std::cerr << "error loading font file" << std::endl;
		hasError = true;
	}
}

Graphics::~Graphics()
{	
	TTF_Quit();
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void Graphics::render(Scene& scene)
{	
	SDL_RenderClear(rend);

	for (const auto& viewComponent : scene.views) {		
		if (viewComponent.visible && scene.positions.hasComponent(viewComponent.getEntity())) {
			auto& positionComponent = scene.positions.getComponent(viewComponent.getEntity());

			SDL_Rect screenRect = { static_cast<int>(positionComponent.x - viewComponent.width / 2), static_cast<int>(positionComponent.y - viewComponent.height/ 2), viewComponent.width, viewComponent.height };
			SDL_Point center = { static_cast<int>(positionComponent.x + viewComponent.width / 2), static_cast<int>(positionComponent.y + viewComponent.height / 2) };
			auto clockwiseRotation = -(positionComponent.yaw + viewComponent.imageBaseRotation);
			SDL_RenderCopyEx(rend, resourceManager.getTexture(viewComponent.textureKey), NULL, &screenRect, clockwiseRotation, NULL, SDL_FLIP_NONE);
		}
	}

	for (const auto& text : scene.textViews) {
		if (text.visible && scene.positions.hasComponent(text.getEntity())) {

			auto& position = scene.positions.getComponent(text.getEntity());
			SDL_Texture* textTexture;
			int width;
			int height;
			std::tie(textTexture, width, height) = resourceManager.getText(rend, text.text);
			SDL_Rect screenRect = { static_cast<int>(position.x - width / 2), static_cast<int>(position.y - height / 2), width, height };
			SDL_RenderCopy(rend, textTexture, NULL, &screenRect);
			SDL_DestroyTexture(textTexture);
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
