#include "TitleScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/UIManager.hpp"
#include <iostream>


void TitleScene::Init()
{
	UIManager::GetInstance().Init_TitleScene();
}


void TitleScene::Update(float dt)
{
	UIManager::GetInstance().Update_TitleScene(dt);
}

void TitleScene::Render(sf::RenderWindow& window)
{
	UIManager::GetInstance().Render_TitleScene(window);

}

void TitleScene::Release()
{
}
