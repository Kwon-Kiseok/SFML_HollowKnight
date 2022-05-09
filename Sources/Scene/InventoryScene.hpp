#pragma once
#include <SFML/Graphics.hpp>
#include "../Items/Coin.hpp"

using namespace sf;

class InventoryScene 
{
private:
	Coin coin;

	Texture textureBackUI;
	Sprite spriteBackUI;

	Texture textureFrameLT;
	Sprite spriteFrameLT;
	Texture textureFrameCT;
	Sprite spriteFrameCT;
	Texture textureFrameRT;
	Sprite spriteFrameRT;
	Texture textureFrameLB;
	Sprite spriteFrameLB;
	Texture textureFrameCB;
	Sprite spriteFrameCB;
	Texture textureFrameRB;
	Sprite spriteFrameRB;

	Texture textureHealth;
	Sprite spriteHealth;

	Texture textureSoul;
	Sprite spriteSoul;

	Texture textureSpellCore;
	Sprite spriteSpellCore;

	Texture textureNail;
	Sprite spriteNail;

	Texture textureInvenCoin;
	Sprite spriteInvenCoin;

	Font fontCALIST;
	Text textInven;

	Text textCoin;

	bool visible = false;

public:
	InventoryScene() {}
	virtual ~InventoryScene() noexcept = default;

	void Init();
	void Update(float dt);
	void Render(sf::RenderWindow & window);
	void Release();

	void SetVisible(bool is);
	bool GetVisible();

};

