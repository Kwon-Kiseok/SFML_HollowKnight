#include "TextureManager.hpp"

Texture& TextureManager::GetTexture(std::string filename)
{
	// 1. filename key가 map에 존재하는가
	// 2-1. 존재하는 경우 -> map에 찾아서 반환한다.
	// 2-2. 존재하지 않는 경우 -> 만들어서 map에 insert 한다.
	auto& map = mapTexture;

	auto it = map.find(filename);
	if (it == map.end())
	{
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}

	return map[filename];
}
