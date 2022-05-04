#pragma once
#include "Scene.hpp"
#include "InventoryScene.hpp"

class TempUIScene : public Scene
{
private:
	InventoryScene inventory;

public:
	TempUIScene() {}
	virtual ~TempUIScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow & window) override;
	virtual void Release() override;
};

