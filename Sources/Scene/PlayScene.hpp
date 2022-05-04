#pragma once
#include "Scene.hpp"
#include "../Player/Player.hpp"
#include "../DemoTile.hpp"

using namespace sf;
class PlayScene	: public Scene
{
private:
	Texture textureCharacterUI;
	Sprite spriteCharacterUI;

	Texture textureCoin;
	Sprite spriteCoin;

	Texture textureLife;
	Sprite spriteLife;
	const int countLife = 5;

	Font fontArial;
	Text textCoin;

	Player* player;
	// Å×½ºÆ® Å¸ÀÏ
	DemoTile* tile;
public:
	PlayScene() {}
	virtual ~PlayScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow & window) override;
	virtual void Release() override;

};

