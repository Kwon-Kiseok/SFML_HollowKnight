#include "TextureManager.hpp"

Texture& TextureManager::GetTexture(std::string filename)
{
	// 1. filename key�� map�� �����ϴ°�
	// 2-1. �����ϴ� ��� -> map�� ã�Ƽ� ��ȯ�Ѵ�.
	// 2-2. �������� �ʴ� ��� -> ���� map�� insert �Ѵ�.
	auto& map = mapTexture;

	auto it = map.find(filename);
	if (it == map.end())
	{
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}

	return map[filename];
}
