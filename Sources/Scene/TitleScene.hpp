#pragma once
#include "Scene.hpp"

class TitleScene : public Scene
{
public:
	TitleScene() {}
	virtual ~TitleScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Release() override;
};

