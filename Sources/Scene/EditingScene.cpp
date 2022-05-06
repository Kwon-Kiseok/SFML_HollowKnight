#include "EditingScene.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Utils/Utility.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/BackgroundImages.hpp"
#include "../Framework/Game.hpp"

#include <iostream>

EditingScene::EditingScene() noexcept
{
	positionSetting = false;
}

void EditingScene::Init()
{
	layer = 0;

	groundButton = new button("ground", Vector2f(1850.f, 300.f), Vector2f(100.f, 25.f));
	layeredButton = new button("layered", Vector2f(1850.f, 400.f), Vector2f(100.f, 25.f));
	buildingButton = new button("building", Vector2f(1850.f, 500.f), Vector2f(100.f, 25.f));
	backgroundButton = new button("bg", Vector2f(1850.f, 600.f), Vector2f(100.f, 25.f));

}

void EditingScene::Update(float dt)
{
	groundButton->update();
	MoveView();

	/*if (Game::GetInstance().GetTextBox().GetSelected())
	{
		if (InputManager::GetInstance().GetKeyDown(Keyboard::Key::Enter))
		{
			inputIndex = Game::GetInstance().GetTextBox().getText();

			inputImageIdx = stoi(inputIndex);
			layer = stoi(inputLayer);
		}
	}*/


	if(groundButton->IsButtonClicked() && !positionSetting)
	{
		positionSetting = true;

		Game::GetInstance().GetTextBox().setSelected(true);

		object = new Ground(0);
		object->SetLayer(0);
		
		groundButton->ResetIsClicked();
	}

	layeredButton->update();
	
	if (layeredButton->IsButtonClicked() && !positionSetting)
	{
		positionSetting = true;

		inputImageIdx = Utility::Random(1, 36);

		object = new TownLayered(inputImageIdx);
		object->SetLayer(0);

		layeredButton->ResetIsClicked();
	}

	buildingButton->update();
	
	if (buildingButton->IsButtonClicked() && !positionSetting)
	{
		positionSetting = true;


		buildingButton->ResetIsClicked();
	}
	
	backgroundButton->update();

	if (backgroundButton->IsButtonClicked() && !positionSetting)
	{
		positionSetting = true;

		backgroundButton->ResetIsClicked();
	}

	if (object != nullptr && positionSetting)
	{
		object->SetPosition(InputManager::GetInstance().GetMouseWorldPosition());

		if (InputManager::GetInstance().GetKeyDown(Keyboard::Space))
		{
			objects.push_back(object);
			positionSetting = false;
		}
		else if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Right))
		{
			object = nullptr;
			positionSetting = false;
		}
	}
}

void EditingScene::Render(sf::RenderWindow& window)
{
	if (nullptr != object)
	{
		object->Render(window);
	}

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		(*it)->Render(window);
	}

	window.setView(ViewManager::GetInstance().GetUiView());
	ViewManager::GetInstance().draw(window);
	groundButton->draw(window);
	layeredButton->draw(window);
	buildingButton->draw(window);
	backgroundButton->draw(window);
}

void EditingScene::Release()
{
	delete groundButton;
	delete layeredButton;
	delete buildingButton;
	delete backgroundButton;

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		delete (*it);
		(*it) = nullptr;
		count++;
	}
	std::cout << count << std::endl;
	objects.clear();
}

void EditingScene::MoveView()
{
	if (InputManager::GetInstance().GetKey(Keyboard::Right))
	{
		ViewManager::GetInstance().GetMainView().move(1.f, 0.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Left))
	{
		ViewManager::GetInstance().GetMainView().move(-1.f, 0.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Up))
	{
		ViewManager::GetInstance().GetMainView().move(0.f, -1.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Down))
	{
		ViewManager::GetInstance().GetMainView().move(0.f, 1.f);
	}
}
