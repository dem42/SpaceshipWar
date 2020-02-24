#pragma once

#include <unordered_map>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

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

	void loadTexture(SDL_Renderer* renderer, TextureKey& key);
	SDL_Texture* getTexture(const TextureKey& key);

private:
	std::unordered_map<TextureKey, SDL_Texture*, TextureHash> textureBank;
};