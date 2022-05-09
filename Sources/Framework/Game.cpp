#include "Game.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"


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
    SceneManager::GetInstance().Init();
    InputManager::GetInstance().Init();
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
        if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Escape))
        {
            window->close();
            return;
        }

        InputManager::GetInstance().Update(dt.asSeconds(), *window, ViewManager::GetInstance().GetMainView());
        SceneManager::GetInstance().Update(dt.asSeconds());

        Render();
    }
}

void Game::Render()
{
    window->clear();
    window->setView(ViewManager::GetInstance().GetMainView());
    SceneManager::GetInstance().Render(*window);
    window->display();
}

void Game::Release()
{
    ViewManager::GetInstance().ClearView();
    SceneManager::GetInstance().Release();
    SoundManager::GetInstance().Release();
}