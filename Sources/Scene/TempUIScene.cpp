#include "TempUIScene.h"
#include "../Managers/InputManager.hpp"
#include "InventoryScene.hpp"

void TempUIScene::Init()
{
}

void TempUIScene::Update(float dt)
{
	// 인벤토리가 꺼져있을 때는 -> true
	// 켜져있을 때 -> false
	if (InputManager::GetInstance().GetKeyDown(Keyboard::I))
	{
		// toggle() 
		inventory.SetVisible();
	}
}

void TempUIScene::Render(sf::RenderWindow& window)
{
	if (inventory.GetVisible())
		inventory.Render(window);
}

void TempUIScene::Release()
{
}
