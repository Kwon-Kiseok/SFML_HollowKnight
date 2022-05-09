#include "EditingScene.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Utils/Utility.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Objects/Stable/Stable.hpp"
#include "../Objects/Stable/BackgroundImages.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/bench.hpp"
#include "../Objects/Stable/Portal.hpp"

#include <iostream>
#include <ostream>
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
	backboard.setFillColor(Color(51,51,51));
	backboard.setSize(Vector2f(3000.f, 1000.f));

	font.loadFromFile("Resources/Fonts/CALIST.TTF");
	currentCursorPos.setFont(font);
	currentCursorPos.setCharacterSize(20);
	currentCursorPos.setPosition(10.f, 10.f);
	currentCursorPos.setFillColor(Color::White);

	layerIndicator.setFont(font);
	layerIndicator.setCharacterSize(20);
	layerIndicator.setPosition(ViewManager::GetInstance().GetResolution().x - 260.f, 420.f);
	layerIndicator.setFillColor(Color::White);

	manualText.setFont(font);
	manualText.setCharacterSize(20);
	manualText.setFillColor(Color::Magenta);
	
	// 버튼 생성
	groundButton = new button("ground", Vector2f(ViewManager::GetInstance().GetResolution().x-100.f, 300.f), Vector2f(100.f, 25.f));
	layeredButton = new button("layered", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 330.f), Vector2f(100.f, 25.f));
	buildingButton = new button("building", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 360.f), Vector2f(100.f, 25.f));
	backgroundButton = new button("bg", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 390.f), Vector2f(100.f, 25.f));
	graveCrossButton = new button("graveCross", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 420.f), Vector2f(100.f, 25.f));
	extraButton = new button("extra", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 450.f), Vector2f(100.f, 25.f));
	benchButton = new button("bench", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 480.f), Vector2f(100.f, 25.f));
	portalButton = new button("portal", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 510.f), Vector2f(100.f, 25.f));

	saveButton = new button("Save", Vector2f(ViewManager::GetInstance().GetResolution().x - 300.f, 950.f), Vector2f(90.f, 30.f));
	loadButton = new button("Load", Vector2f(ViewManager::GetInstance().GetResolution().x - 200.f, 950.f), Vector2f(90.f, 30.f));
	exitButton = new button("Exit", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 950.f), Vector2f(90.f, 30.f));

	objectButtons.push_back(groundButton);
	objectButtons.push_back(layeredButton);
	objectButtons.push_back(buildingButton);
	objectButtons.push_back(backgroundButton);
	objectButtons.push_back(graveCrossButton);
	objectButtons.push_back(extraButton);
	objectButtons.push_back(benchButton);
	objectButtons.push_back(portalButton);

	objectButtons.push_back(saveButton);
	objectButtons.push_back(loadButton);
	objectButtons.push_back(exitButton);
}

void EditingScene::Update(float dt)
{
	// 마우스 조작법 표시
	SetManual();
	// 방향키로 화면 이동
	MoveView();
	// 현재 커서 위치 보여줌
	CursorPosView();
	// 배치된 오브젝트들 정보 보기
	ViewObjectsInfos();
	// 배치된 오브젝트 선택
	ClickObject();

	// 어떤 오브젝트 클래스 버튼이 눌렸는지 검사
	for (auto button : objectButtons)
	{
		button->update();

		if (saveButton->IsButtonClicked())
		{
			Save();
			saveButton->ResetIsClicked();
		}
		else if (loadButton->IsButtonClicked())
		{
			Load();
			loadButton->ResetIsClicked();
		}

		ObjectSeleted(*button);
	}

	// 오브젝트가 선택되었다면 
	SetImageIndex();
	// 레이어 설정
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
	for (auto button : objectButtons)
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
	window.draw(manualText);
}

void EditingScene::Release()
{
	for (auto button : objectButtons)
	{
		delete button;
		button = nullptr;
	}
	objectButtons.clear();

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		delete (*it);
		(*it) = nullptr;
		count++;
	}
	objects.clear();
}

void EditingScene::ObjectSeleted(button& button)
{
	if (button.GetText() == "Save" || button.GetText() == "Load" || button.GetText() == "Exit")
	{
		return;
	}
	else if (button.IsButtonClicked() && !positionSetting)
	{
		selectName = button.GetText();
		//std::cout << selectName << std::endl;
		OpenImageIndex(button);
		button.ResetIsClicked();
	}
}

void EditingScene::OpenImageIndex(button& btn)
{
	if (!btn.IsButtonClicked())
		return;
	else
	{
		// 이미 열려있었다면 초기화
		if (!ImageIndexList.empty())
		{
			for (auto object : ImageIndexList)
			{
				delete object;
				object = nullptr;
			}
			ImageIndexList.clear();
		}

		Stable* temp = nullptr;
		if (selectName == "ground")
		{
			temp = new Ground();
		}
		else if (selectName == "layered")
		{
			temp = new TownLayered();
		}
		else if (selectName == "building")
		{
			temp = new TownBuilding();
		}
		else if (selectName == "bg")
		{
			temp = new TownBG();
		}
		else if (selectName == "graveCross")
		{
			temp = new TownGraveCross();
		}
		else if (selectName == "extra")
		{
			temp = new TownExtra();
		}
		else if (selectName == "bench")
		{
			temp = new Bench();
			stringstream ss;
			ss << 1;
			button* objectName = new button(ss.str(), Vector2f(ViewManager::GetInstance().GetResolution().x - 175.f, 10.f), Vector2f(50.f, 25.f));
			ImageIndexList.push_back(objectName);
			return;
		}
		else if (selectName == "portal")
		{
			temp = new Portal();
			stringstream ss;
			ss << 1;
			button* objectName = new button(ss.str(), Vector2f(ViewManager::GetInstance().GetResolution().x - 175.f, 10.f), Vector2f(50.f, 25.f));
			ImageIndexList.push_back(objectName);
			return;
		}
		for (int i = 0; i < temp->GetIndexTotal(); ++i)
		{
			stringstream ss;
			ss << (i + 1);
			button* objectName = new button(ss.str(), Vector2f(ViewManager::GetInstance().GetResolution().x - 175.f, 10.f + (i * 30.f)), Vector2f(25.f, 25.f));
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
		plusLayerButton = new button("+", Vector2f(ViewManager::GetInstance().GetResolution().x - 250.f, 400.f), Vector2f(25.f, 25.f));
		minusLayerButton = new button("-", Vector2f(ViewManager::GetInstance().GetResolution().x - 250.f, 460.f), Vector2f(25.f, 25.f));
		confirmLayerButton = new button("OK", Vector2f(ViewManager::GetInstance().GetResolution().x - 225.f, 430.f), Vector2f(25.f, 25.f));
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
		else if (selectName == "portal")
		{
			this->object = new Portal();
		}
		else if (selectName == "building")
		{
			this->object = new TownBuilding(inputImageIdx);
		}
		else if (selectName == "bg")
		{
			this->object = new TownBG(inputImageIdx);
		}
		else if (selectName == "graveCross")
		{
			this->object = new TownGraveCross(inputImageIdx);
		}
		else if (selectName == "extra")
		{
			this->object = new TownExtra(inputImageIdx);
		}
		else if (selectName == "bench")
		{
			this->object = new Bench();
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
	if (object == nullptr)
		return;

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
			if (!selectObject)
				objects.push_back(object);
			else
				selectObject = false;
			positionSetting = false;
		}
		else if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Right))
		{
			if (selectObject == true)
			{
				object->SetPosition(prevPos);
			}

			object = nullptr;
			selectObject = false;
			positionSetting = false;
		}
		else if (InputManager::GetInstance().GetKeyDown(Keyboard::BackSpace))
		{
			for (auto it = objects.begin(); it != objects.end(); ++it)
			{
				if ((*it) == object)
				{
					objects.erase(it);
					break;
				}
			}
			object = nullptr;
			selectObject = false;
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
	editData = "X: " + ss.str();
	ss.str("");
	ss << InputManager::GetInstance().GetMouseWorldPosition().y;
	editData += " Y: " + ss.str();
	ss.str("");
	ss << InputManager::GetInstance().GetCurrentZoom();
	editData += "\nZoom: " + ss.str();
	ss.str("");
	ss << objects.size();
	editData += "\nObjects Size: " + ss.str();

	currentCursorPos.setString(editData);
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

void EditingScene::ClickObject()
{
	if (selectObject == true)
		return;

	for (auto object : objects)
	{
		if (object->GetSprite().getGlobalBounds().contains(InputManager::GetInstance().GetMouseWorldPosition()))
		{
			if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Left))
			{
				selectObject = true;
				this->object = object;
				prevPos = object->GetPosition();
				positionSetting = true;
			}
		}
	}
}

void EditingScene::SetManual()
{
	manualText.setPosition(static_cast<Vector2f>(InputManager::GetInstance().GetMousePosition()));
	
	if(positionSetting)
	{
		manualText.setString(L"RIGHT - undo\nSPACE - put\nBACK SPACE - delete");
	}
	else
	{
		manualText.setString(L"LEFT - select");
	}
}

void EditingScene::Save()
{
	ofstream dataFile;
	dataFile.open("data_tables/maps/Town_map_data.csv");
	if (dataFile.fail())
	{
		cout << "File load Failed" << endl;
		return;
	}
	dataFile << "NAME,INDEX,LAYER,X,Y\n";
	for (int i = 0; i < objects.size(); ++i)
	{
		dataFile << objects[i]->GetName() << "," << objects[i]->GetImageIdx() 
			<< "," << objects[i]->GetLayer() << "," << objects[i]->GetPosition().x 
			<< "," << objects[i]->GetPosition().y << endl;
	}
	cout << "Save Complete File" << endl;
	dataFile.close();
}

void EditingScene::Load()
{
	rapidcsv::Document dataFile("data_tables/maps/Town_map_data.csv");

	vector<string> colName = dataFile.GetColumn<string>("NAME");
	vector<int> colIndex = dataFile.GetColumn<int>("INDEX");
	vector<int> colLayer = dataFile.GetColumn<int>("LAYER");
	vector<float> colX = dataFile.GetColumn<float>("X");
	vector<float> colY = dataFile.GetColumn<float>("Y");

	int totalObjects = colName.size();
	for (int i = 0; i < totalObjects; ++i)
	{
		MapData data;
		data.name = colName[i];
		data.index = colIndex[i];
		data.layer = colLayer[i];
		data.x = colX[i];
		data.y = colY[i];

		AddObject(data);
		objects.push_back(object);
	}

	cout << "Load Complete" << endl;
}

void EditingScene::AddObject(MapData& data)
{
	if (data.name == "ground")
	{
		this->object = new Ground(data.index);
	}
	else if (data.name == "layered")
	{
		this->object = new TownLayered(data.index);
	}
	else if (data.name == "portal")
	{
		this->object = new Portal();
	}
	else if (data.name == "building")
	{
		this->object = new TownBuilding(data.index);
	}
	else if (data.name == "bg")
	{
		this->object = new TownBG(data.index);
	}
	else if (data.name == "graveCross")
	{
		this->object = new TownGraveCross(data.index);
	}
	else if (data.name == "extra")
	{
		this->object = new TownExtra(data.index);
	}
	else if (data.name == "bench")
	{
		this->object = new Bench();
	}

	this->object->SetLayer(data.layer);
	this->object->SetPosition(Vector2f(data.x, data.y));
	this->object->SetOriginCenter();
}
