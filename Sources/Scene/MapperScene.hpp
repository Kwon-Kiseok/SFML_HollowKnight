#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
class MapperScene :public Scene
{
private:
	Texture textureHomeBG;
	Sprite spriteHomeBG;

	Texture textureHome;
	Sprite spriteHome;
	Texture textureDesk;
	Sprite spriteDesk;
	Texture textureLight;
	Sprite spriteLight;

	Texture textureIsadela;
	Sprite spriteIsadela;
public:
	MapperScene() {}
	virtual ~MapperScene()noexcept = default;

	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);
	void Release();
};

