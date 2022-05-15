#include "Game.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/UIManager.hpp"
#include "../Animation/rapidcsv.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

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
    LoadingScreen();
    LoadingScereenLoad();

    while (window->isOpen())
    {
        status = future.wait_for(0ms);
        if (status != std::future_status::ready)
        {
            loadingAnimController.Update(clock.restart().asSeconds());
        }
        else
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
        }
        Render();
    }
}

void Game::Render()
{
    if (status != std::future_status::ready)
    {
        window->clear(sf::Color::Black);
              
        window->draw(m_loadingSpr);
        window->draw(m_animSpr);
        window->draw(m_loadingText);
              
        window->display();
    }
    else
    {
        window->clear();
        window->setView(ViewManager::GetInstance().GetMainView());
        SceneManager::GetInstance().Render(*window);

        window->setView(ViewManager::GetInstance().GetUiView());
        UIManager::GetInstance().Render(*window);
        window->display();
    }
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

void Game::LoadingScreen()
{

    if (!m_loadingTex.loadFromFile("Resources/Sprite/UI/Team Cherry Logo_large.png"))
    {
        std::cout << " \"assets/images/sencan.png\" is not exsist\n";
    }
    m_loadingSpr.setTexture(m_loadingTex);
    m_loadingSpr.setOrigin(m_loadingTex.getSize().x / 2, m_loadingTex.getSize().y / 2);
    m_loadingSpr.setPosition(ViewManager::GetInstance().GetResolution().x >> 1, (ViewManager::GetInstance().GetResolution().y >> 1) + m_loadingTex.getSize().y / 30);

    m_animSpr.setOrigin((m_animTex.getSize().x * 0.3f) / 2, (m_animTex.getSize().y * 0.3f) / 2);
    m_animSpr.setPosition(ViewManager::GetInstance().GetResolution().x - 100, ViewManager::GetInstance().GetResolution().y - 100);
    loadingAnimController.SetTarget(&m_animSpr);
    SetAnimation();

    if (!m_loadingFont.loadFromFile("Resources/Fonts/CALIST.TTF"))
    {
        std::cout << " \"assets/images/loading.png\" is not exsist\n";
    }
    m_loadingText.setFont(m_loadingFont);
    m_loadingText.setFillColor(sf::Color::White);
    m_loadingText.setString("LOADING");
    m_loadingText.setCharacterSize(24);
    m_loadingText.setPosition(m_animSpr.getPosition().x - m_loadingText.getLocalBounds().width/2, m_animSpr.getPosition().y + 40);

    
}

void Game::Setup()
{
    //Initialize here
    std::cout << "Loading Setup" << std::endl;
    // ´ë±â
    loadingAnimController.Play("Loading");
    std::this_thread::sleep_for(5s);

    return;
}

void Game::SetAnimation()
{
    rapidcsv::Document clips("data_tables/animations/ui/loading_anim_clips.csv");

    std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
    std::vector<int> colFps = clips.GetColumn<int>("FPS");
    std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
    std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

    int totalClips = colId.size();
    for (int i = 0; i < totalClips; ++i)
    {
        AnimationClip clip;
        clip.id = colId[i];
        clip.fps = colFps[i];
        clip.loopType = (AnimationLoopTypes)colLoop[i];

        rapidcsv::Document frames(colPath[i]);
        std::vector<std::string> colTexure = frames.GetColumn<std::string>("TEXTURE PATH");
        std::vector<int> colL = frames.GetColumn<int>("L");
        std::vector<int> colT = frames.GetColumn<int>("T");
        std::vector<int> colW = frames.GetColumn<int>("W");
        std::vector<int> colH = frames.GetColumn<int>("H");

        std::vector<int> colX = frames.GetColumn<int>("X");
        std::vector<int> colY = frames.GetColumn<int>("Y");

        int totalFrames = colTexure.size();
        for (int j = 0; j < totalFrames; ++j)
        {
            if (texMap.find(colTexure[j]) == texMap.end())
            {
                auto& ref = texMap[colTexure[j]];
                ref.loadFromFile(colTexure[j]);
            }
            clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j]), Vector2f(colX[j], colY[j])));
        }

        loadingAnimController.AddClip(clip);
    }
}

void Game::LoadingScereenLoad()
{
    future = std::async(std::launch::async, [&]
        {
            return Setup();
        });

    if (status == std::future_status::ready)
    {
        status = std::future_status::timeout;
        status = future.wait_for(0ms);
        std::cout << "status" << std::endl;
    }
    
}
