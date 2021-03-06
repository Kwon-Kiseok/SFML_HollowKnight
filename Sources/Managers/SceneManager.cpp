#include "SceneManager.hpp"
#include "../Scene/TitleScene.hpp"
#include "../Scene/PlayScene.hpp"
#include "../Scene/EditingScene.hpp"
#include "../Managers/ViewManager.hpp"


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
	Scenes[L"Play"] = new PlayScene();
	Scenes[L"Editor"] = new EditingScene();

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
	ViewManager::GetInstance().ClearView();
	ViewManager::GetInstance().Init();
	nextScene = Scenes[sceneName];
	currentScene->Release();
	currentScene = nextScene;
	currentScene->Init();
	nextScene = nullptr;
}
