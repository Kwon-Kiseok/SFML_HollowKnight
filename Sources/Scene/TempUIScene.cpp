#include "TempUIScene.h"
#include "../Managers/InputManager.hpp"
#include "InventoryScene.hpp"

void TempUIScene::Init()
{
}

void TempUIScene::Update(float dt)
{
	// �κ��丮�� �������� ���� -> true
	// �������� �� -> false
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
