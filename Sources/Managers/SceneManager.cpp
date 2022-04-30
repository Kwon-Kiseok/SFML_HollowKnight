#include "SceneManager.hpp"
#include "../Scene/TitleScene.hpp"

SceneManager::~SceneManager() noexcept
{
	currentScene = nullptr;
	nextScene = nullptr;

	for (auto& iter : Scenes)
	{
		delete iter.second;
	}
	Scenes.clear();
}

void SceneManager::Init()
{
	Scenes[L"Title"] = new TitleScene();

	currentScene = Scenes[L"Title"];
	currentScene->Init();
}

void SceneManager::Update(float dt)
{
	currentScene->Update(dt);
}

void SceneManager::Render(sf::RenderWindow& window)
{
	currentScene->Render(window);
}

void SceneManager::Release()
{
	currentScene->Release();
}

void SceneManager::Load(const std::wstring& sceneName)
{
	nextScene = Scenes[sceneName];
	currentScene->Release();
	currentScene = nextScene;
	currentScene->Init();
	nextScene = nullptr;
}
