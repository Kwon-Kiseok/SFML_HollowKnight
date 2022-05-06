#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Item 
{
public:
	Item();
	virtual ~Item();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(RenderWindow& window);
	virtual void Release();


};

