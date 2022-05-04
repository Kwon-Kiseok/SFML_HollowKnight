#pragma once
#include <SFML/Graphics.hpp>
class Map
{
public:
	Map() {}
	virtual ~Map() {}

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual void Release() = 0;
};

