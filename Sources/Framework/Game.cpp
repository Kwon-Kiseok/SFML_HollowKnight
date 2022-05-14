#include "Game.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/UIManager.hpp"


Game::~Game() noexcept
{
    delete window;
    window = nullptr;
}

void Game::Init()
{
    ViewManager::GetInstance().Init();
    window = new RenderWindow(sf::VideoMode(ViewManager::GetInstance().GetResolution().x
        ,ViewManager::GetInstance().GetResolution().y), "Hollow Knight", Style::Fullscreen);
    window->setMouseCursorVisible(false);

    SceneManager::GetInstance().Init();
    InputManager::GetInstance().Init();
    SoundManager::GetInstance().Init();
    UIManager::GetInstance().Init();
}

void Game::Update()
{
    while (window->isOpen())
    {
        Time dt = clock.restart();
        sf::Event event;
        InputManager::GetInstance().ClearInput();
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            InputManager::GetInstance().ProcessInput(event);
        }
        if (isGameOver)
        {
            window->close();
            return;
        }

        InputManager::GetInstance().Update(dt.asSeconds(), *window, ViewManager::GetInstance().GetMainView());
        SceneManager::GetInstance().Update(dt.asSeconds());
        UIManager::GetInstance().Update(dt.asSeconds());
        Render();

    }
}

void Game::Render()
{
    window->clear();
    window->setView(ViewManager::GetInstance().GetMainView());
    SceneManager::GetInstance().Render(*window);

    window->setView(ViewManager::GetInstance().GetUiView());
    UIManager::GetInstance().Render(*window);
    window->display();
}

void Game::Release()
{
    ViewManager::GetInstance().ClearView();
    SceneManager::GetInstance().Release();
    SoundManager::GetInstance().Release();
}

bool Game::GetIsGameOver()
{
    return isGameOver;
}

void Game::SetIsGameOver(bool is)
{
    isGameOver = is;
}

sf::RenderWindow& Game::GetWindow()
{
    return *window;
}
