#pragma once
#include "Scene.hpp"

class TitleScene : public Scene
{
private:
	sf::Texture textureBG;
	sf::Sprite spriteBG;

	sf::Texture textureBeamEffect;
	sf::Sprite spriteBeamEffect;

	sf::Texture textureTitle;
	sf::Sprite spriteTitle;

public:
	TitleScene() {}
	virtual ~TitleScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Release() override;
};

