#include "SceneManager.hpp"
#include "../Scene/TitleScene.hpp"
#include "../Scene/ManagerTestScene.hpp"
#include "../Scene/PlayScene.hpp"
#include "../Scene/EditingScene.hpp"
#include "../Scene/MapTestPlayScene.hpp"


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
	Scenes[L"TestScene"] = new ManagerTestScene();
	Scenes[L"Title"] = new TitleScene();
	Scenes[L"Play"] = new PlayScene();
	Scenes[L"Editor"] = new EditingScene();
	Scenes[L"MapTest"] = new MapTestPlayScene();
	currentScene = Scenes[L"MapTest"];
	//currentScene = Scenes[L"Play"];

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
