#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

using namespace sf;

class InventoryScene : public Scene
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

public:
	InventoryScene() {}
	virtual ~InventoryScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow & window) override;
	virtual void Release() override;

};

