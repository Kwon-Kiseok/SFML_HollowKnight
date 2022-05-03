#pragma once
#include "Scene.hpp"

using namespace sf;
class PlayScene	: public Scene
{
private:
	Texture textureLife1;
	Sprite spriteLife1;

	Texture textureLife2;
	Sprite spriteLife2;
	Texture textureLife3;
	Sprite spriteLife3;
	Texture textureLife4;
	Sprite spriteLife4;
	Texture textureLife5;
	Sprite spriteLife5;

	Texture textureCharacterUI;
	Sprite spriteCharacterUI;

	Texture textureCoin;
	Sprite spriteCoin;

	Font fontCALIST;
	Text textCoin;

public:
	PlayScene() {}
	virtual ~PlayScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow & window) override;
	virtual void Release() override;

};

