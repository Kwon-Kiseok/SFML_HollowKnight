#pragma once
#include "Scene.hpp"

class ManagerTestScene : public Scene
{
private:
	sf::Texture textureBG;
	sf::Sprite spriteBG;
public:
	ManagerTestScene() noexcept;
	~ManagerTestScene() noexcept;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Release() override;
};

