#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"
#include "../Utils/Textbox.hpp"

class Game : public Singleton<Game>
{
private:
	sf::RenderWindow* window;
	sf::Clock clock;

	sf::Font font;
	Textbox* textBox;
public:
	Game() noexcept = default;
	~Game() noexcept;

	void Init();
	void Update();
	void Render();
	void Release();

	Textbox& GetTextBox();
};

