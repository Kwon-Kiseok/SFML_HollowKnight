#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class InventoryScene 
{
private:
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

	Font fontCALIST;
	Text textInven;

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

