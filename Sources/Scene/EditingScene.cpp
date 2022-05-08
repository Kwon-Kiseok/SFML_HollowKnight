#include "EditingScene.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Utils/Utility.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/BackgroundImages.hpp"

#include <iostream>
#include <sstream>

EditingScene::EditingScene() noexcept
{
	positionSetting = false;
	layer = 0;
	isTabClicked = false;
}

void EditingScene::Init()
{
	backboard.setPosition(0.f, 0.f);
	backboard.setFillColor(Color(128,128,128));
	backboard.setSize(Vector2f(5000.f, 4000.f));

	font.loadFromFile("Resources/Fonts/CALIST.TTF");
	currentCursorPos.setFont(font);
	currentCursorPos.setCharacterSize(20);
	currentCursorPos.setPosition(10.f, 10.f);
	currentCursorPos.setFillColor(Color::White);

	layerIndicator.setFont(font);
	layerIndicator.setCharacterSize(20);
	layerIndicator.setPosition(1690.f, 420.f);
	layerIndicator.setFillColor(Color::White);
	
	groundButton = new button("ground", Vector2f(1850.f, 300.f), Vector2f(100.f, 25.f));
	layeredButton = new button("layered", Vector2f(1850.f, 400.f), Vector2f(100.f, 25.f));
	buildingButton = new button("building", Vector2f(1850.f, 500.f), Vector2f(100.f, 25.f));
	backgroundButton = new button("bg", Vector2f(1850.f, 600.f), Vector2f(100.f, 25.f));

	saveButton = new button("Save", Vector2f(1725.f, 950.f), Vector2f(100.f, 30.f));
	exitButton = new button("Exit", Vector2f(1850.f, 950.f), Vector2f(100.f, 30.f));

	buttons.push_back(groundButton);
	buttons.push_back(layeredButton);
	buttons.push_back(buildingButton);
	buttons.push_back(backgroundButton);
	buttons.push_back(saveButton);
	buttons.push_back(exitButton);
}

void EditingScene::Update(float dt)
{
	// 방향키로 화면 이동
	MoveView();
	// 현재 커서 위치 보여줌
	CursorPosView();
	ViewObjectsInfos();
	// 어떤 오브젝트 클래스 버튼이 눌렸는지 검사
	for (auto button : buttons)
	{
		button->update();
		ObjectSeleted(*button);
	}
	// 오브젝트가 선택되었다면 
	SetImageIndex();

	if (checkImageIdx)
		SetLayer();
	// 위치 설정
	SetObjectsPosition();
}

void EditingScene::Render(sf::RenderWindow& window)
{
	window.draw(backboard);

	if (nullptr != object)
	{
		object->Render(window);
	}
	
	for (int i = MAX_LAYER; i >= MIN_LAYER; --i)
	{
		for (auto it = objects.begin(); it != objects.end(); ++it)
		{
			if((* it)->GetLayer() == i)
				(*it)->Render(window);
		}
	}

	if (isTabClicked)
	{
		for (auto status : objectStatuses)
		{
			window.draw(*status);
		}
	}

	// ui
	window.setView(ViewManager::GetInstance().GetUiView());
	ViewManager::GetInstance().draw(window);
	for (auto button : buttons)
	{
		button->draw(window);
	}
	for (auto index : ImageIndexList)
	{
		index->draw(window);
	}

	if (plusLayerButton != nullptr && minusLayerButton != nullptr && confirmLayerButton != nullptr)
	{
		plusLayerButton->draw(window);
		minusLayerButton->draw(window);
		confirmLayerButton->draw(window);
		window.draw(layerIndicator);
	}

	window.draw(currentCursorPos);
}

void EditingScene::Release()
{
	for (auto button : buttons)
	{
		delete button;
		button = nullptr;
	}
	buttons.clear();

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		delete (*it);
		(*it) = nullptr;
		count++;
	}
	std::cout << count << std::endl;
	objects.clear();
}

void EditingScene::ObjectSeleted(button& button)
{
	if (button.IsButtonClicked() && !positionSetting)
	{
		selectName = button.GetText();
		std::cout << selectName << std::endl;
		OpenImageIndex(button);
		button.ResetIsClicked();
	}
}

void EditingScene::OpenImageIndex(button& btn)
{
	if (selectName == "layered" && btn.IsButtonClicked())
	{
		TownLayered temp;
		for (int i = 0; i < temp.GetIndexTotal(); ++i)
		{
			stringstream ss;
			ss << (i+1);
			button* objectName = new button(ss.str(), Vector2f(1780.f, 10.f + (i * 30.f)), Vector2f(25.f, 25.f));
			ImageIndexList.push_back(objectName);
		}
	}
}

void EditingScene::SetImageIndex()
{
	if (!ImageIndexList.empty())
	{
		for (auto index : ImageIndexList)
		{
			index->update();

			if (index->IsButtonClicked())
			{
				inputImageIdx = stoi(index->GetText());
				checkImageIdx = true;
				index->ResetIsClicked();
			}
		}
	}
}

void EditingScene::SetLayer()
{
	// 레이어
	if (plusLayerButton == nullptr && minusLayerButton == nullptr && confirmLayerButton == nullptr)
	{
		plusLayerButton = new button("+", Vector2f(1700.f, 400.f), Vector2f(25.f, 25.f));
		minusLayerButton = new button("-", Vector2f(1700.f, 460.f), Vector2f(25.f, 25.f));
		confirmLayerButton = new button("OK", Vector2f(1730.f, 430.f), Vector2f(25.f, 25.f));
	}
	plusLayerButton->update();
	minusLayerButton->update();
	confirmLayerButton->update();

	stringstream ss;
	ss.str("");
	if (plusLayerButton->IsButtonClicked())
	{
		layer++;
		if (layer > MAX_LAYER)
		{
			layer = MAX_LAYER;
		}
		plusLayerButton->ResetIsClicked();
	}
	if (minusLayerButton->IsButtonClicked())
	{
		layer--;
		if (layer < MIN_LAYER)
		{
			layer = MIN_LAYER;
		}
		minusLayerButton->ResetIsClicked();
	}
	ss << layer;
	layerIndicator.setString(ss.str());

	if (confirmLayerButton->IsButtonClicked())
	{
		if (selectName == "ground")
		{
			this->object = new Ground(inputImageIdx);
		}
		else if (selectName == "layered")
		{
			this->object = new TownLayered(inputImageIdx);
		}

		this->object->SetLayer(layer);
		inputImageIdx = 0;
		positionSetting = true;
		confirmLayerButton->ResetIsClicked();

		delete plusLayerButton;
		delete minusLayerButton;
		delete confirmLayerButton;
		plusLayerButton = nullptr;
		minusLayerButton = nullptr;
		confirmLayerButton = nullptr;
		checkImageIdx = false;
	}
}

void EditingScene::SetObjectsPosition()
{
	if (object != nullptr && positionSetting)
	{
		for (auto object : ImageIndexList)
		{
			delete object;
			object = nullptr;
		}
		ImageIndexList.clear();

		object->SetOriginCenter();
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

void EditingScene::MoveView()
{
	if (InputManager::GetInstance().GetKey(Keyboard::Right)
		|| InputManager::GetInstance().GetKey(Keyboard::D))
	{
		ViewManager::GetInstance().GetMainView().move(1.f, 0.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Left)
		|| InputManager::GetInstance().GetKey(Keyboard::A))
	{
		ViewManager::GetInstance().GetMainView().move(-1.f, 0.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Up)
		|| InputManager::GetInstance().GetKey(Keyboard::W))
	{
		ViewManager::GetInstance().GetMainView().move(0.f, -1.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Down)
		|| InputManager::GetInstance().GetKey(Keyboard::S))
	{
		ViewManager::GetInstance().GetMainView().move(0.f, 1.f);
	}
}

void EditingScene::CursorPosView()
{
	stringstream ss;
	ss << InputManager::GetInstance().GetMouseWorldPosition().x;
	cursorData = "X: " + ss.str();
	ss.str("");
	ss << InputManager::GetInstance().GetMouseWorldPosition().y;
	cursorData += " Y: " + ss.str();
	ss.str("");
	ss << InputManager::GetInstance().GetCurrentZoom();
	cursorData += "\nZoom: " + ss.str();

	currentCursorPos.setString(cursorData);
}

void EditingScene::ViewObjectsInfos()
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Tab))
	{
		isTabClicked = true;

		for (auto object : objects)
		{
			Text* textStatus = new Text();
			stringstream ss;
			ss << object->GetLayer();
			stringStatus = "Layer: " + ss.str();
			ss.str("");
			ss << object->GetPosition().x;
			stringStatus += "\nX: " + ss.str();
			ss.str("");
			ss << object->GetPosition().y;
			stringStatus += "\nY: " + ss.str();
			ss.str("");
			ss << object->GetName();
			stringStatus += "\nName: " + ss.str();

			textStatus->setFont(font);
			textStatus->setCharacterSize(13);
			textStatus->setOrigin(object->GetOrigin());
			textStatus->setPosition(object->GetPosition());
			textStatus->setFillColor(Color::Green);
			textStatus->setString(stringStatus);

			objectStatuses.push_back(textStatus);
		}
	}
	if (InputManager::GetInstance().GetKeyUp(Keyboard::Tab))
	{
		isTabClicked = false;

		for (auto status : objectStatuses)
		{
			delete status;
			status = nullptr;
		}
		objectStatuses.clear();
	}
}
