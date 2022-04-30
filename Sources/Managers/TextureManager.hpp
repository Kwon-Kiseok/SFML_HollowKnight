#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"
#include <map>

using namespace sf;

class TextureManager : public Singleton<TextureManager>
{
private:
	TextureManager() noexcept = default;
	~TextureManager() noexcept = default;

	std::map<std::string, Texture> mapTexture;
public:
	Texture& GetTexture(std::string filename);
};

