#pragma once
#include "Scene.hpp"

using namespace sf;
class PlayScene	: public Scene
{
public:
	PlayScene();
	virtual ~PlayScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow & window) override;
	virtual void Release() override;
};

