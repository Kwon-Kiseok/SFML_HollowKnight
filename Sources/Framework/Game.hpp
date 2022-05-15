#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <future>
#include <string>
#include "../include/Singleton.hpp"
#include "../Animation/AnimationController.hpp"

class Game : public Singleton<Game>
{
private:
	sf::RenderWindow* window;
	sf::Clock clock;
	bool isGameOver = false;
public:
	Game() noexcept = default;
	~Game() noexcept;

	void Init();
	void Update();
	void Render();
	void Release();

	bool GetIsGameOver();
	void SetIsGameOver(bool is);
	sf::RenderWindow& GetWindow();

public:
	std::future<void> future;
	std::future_status status;

	sf::Texture m_loadingTex;
	sf::Sprite m_loadingSpr;

	sf::Texture m_animTex;
	sf::Sprite m_animSpr;
	sf::IntRect rect;

	AnimationController loadingAnimController;
	std::map<std::string, Texture> texMap;

	sf::Font m_loadingFont;
	sf::Text m_loadingText;
	sf::Text m_playText;
public:
	void LoadingScreen();
	void Setup();
	void SetAnimation();
	void LoadingScereenLoad();
};

