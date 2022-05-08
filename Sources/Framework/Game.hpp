#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"

class Game : public Singleton<Game>
{
private:
	sf::RenderWindow* window;
	sf::Clock clock;
public:
	Game() noexcept = default;
	~Game() noexcept;

	void Init();
	void Update();
	void Render();
	void Release();
};

