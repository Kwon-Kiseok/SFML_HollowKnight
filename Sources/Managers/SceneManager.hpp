#pragma once
#include "../include/Singleton.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;
	std::unordered_map<std::wstring, Scene*> Scenes;	// ���� ���ĵǾ� ���� �ʿ伺�� ���� �Ǵ�, unordered_map�� ���

public:
	SceneManager() noexcept = default;
	~SceneManager() noexcept;

public:
	Scene* GetCurrent() { return currentScene; }

	void Init();
	void Update(float dt = 0.f);
	void Render(sf::RenderWindow& window);
	void Release();

	void Load(const std::wstring& sceneName);
};

