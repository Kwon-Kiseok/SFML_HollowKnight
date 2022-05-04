#pragma once
#include "Scene.hpp"

class Map;
class MapTestPlayScene : public Scene
{
private:

public:
	MapTestPlayScene();
	~MapTestPlayScene() noexcept;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Release() override;
};

