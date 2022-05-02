#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"
#include <map>

using namespace sf;

class TextureManager : public Singleton<TextureManager>
{
private:
	std::map<std::string, Texture> mapTexture;
public:
	TextureManager() noexcept = default;
	~TextureManager() noexcept = default;

public:
	Texture& GetTexture(std::string filename);
};

