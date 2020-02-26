#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <unordered_map>
#include <string>
#include <tuple>

struct TextureKey {
	TextureKey(const std::string& path);

	std::string path;
	bool loaded;

	bool operator==(const TextureKey& rhs) const;
};

struct TextureHash
{
	std::size_t operator()(TextureKey const& key) const noexcept;
};

class ResourceManager {
public:
	ResourceManager() = default;
	~ResourceManager();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(const ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;

	bool loadFont(const std::string& fontPath);
	void loadTexture(SDL_Renderer* renderer, TextureKey& key);
	SDL_Texture* getTexture(const TextureKey& key);
	std::tuple<SDL_Texture*, int, int> getText(SDL_Renderer* renderer, const std::string& text);

private:
	std::unordered_map<TextureKey, SDL_Texture*, TextureHash> textureBank;
	TTF_Font* font = nullptr;
	SDL_Color textColor = { 255, 255, 255, 0 };
};