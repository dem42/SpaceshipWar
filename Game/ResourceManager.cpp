#include "Game/ResourceManager.h"

#include <SDL_image.h>
#include <iostream>

ResourceManager::~ResourceManager()
{
	for (auto& textureBankEntry : textureBank) {
		SDL_DestroyTexture(textureBankEntry.second);
	}
}

bool ResourceManager::loadFont(const std::string& fontPath)
{
	font = TTF_OpenFont(fontPath.c_str(), 24);
	return font != nullptr;
}

void ResourceManager::loadTexture(SDL_Renderer* renderer, TextureKey& key)
{	
	if (key.loaded) {
		return;
	}
	if (textureBank.find(key) != textureBank.end()) {
		key.loaded = true;
		return;
	}
	std::cout << "Loading texture " << key.path << std::endl;

	// creates a surface to load an image into the main memory 
	SDL_Surface* surface;

	// please provide a path for your image 
	surface = IMG_Load(key.path.c_str());

	// loads image to our graphics hardware memory. 
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);


	SDL_Rect dest;

	// connects our texture with dest to control position 
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	// adjust height and width of our image box. 
	dest.w /= 6;
	dest.h /= 6;

	// sets initial x-position of object 
	dest.x = (1000 - dest.w) / 2;

	// sets initial y-position of object 
	dest.y = (1000 - dest.h) / 2;


	key.loaded = true;

	textureBank.emplace(key, tex);
}

SDL_Texture* ResourceManager::getTexture(const TextureKey& key)
{
	if (!key.loaded) {
		return nullptr;
	}
	return textureBank[key];
}

std::tuple<SDL_Texture*, int, int> ResourceManager::getText(SDL_Renderer* renderer, const std::string& text)
{	
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	int textWidth = textSurface->w;
	int textHeight = textSurface->h;
	SDL_FreeSurface(textSurface);	
	return std::make_tuple(textTexture, textWidth, textHeight);
}

TextureKey::TextureKey(const std::string& path) : path(path), loaded(false)
{
}

bool TextureKey::operator==(const TextureKey& rhs) const
{
	return path == rhs.path;
}

std::size_t TextureHash::operator()(const TextureKey& key) const noexcept
{
	return std::hash<std::string>{}(key.path);	
}
