#include "EditingScene.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Utils/Utility.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Objects/Stable/Stable.hpp"
#include "../Objects/Stable/BackgroundImages.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/bench.hpp"
#include "../Objects/Stable/Portal.hpp"
#include "../Objects/Stable/Wall.hpp"

#include "../Objects/Stable/Door.hpp"
#include "../Objects/Stable/KingsPassImages.hpp"
#include "../Objects/Stable/Platform.hpp"
#include "../Objects/Stable/thorn.hpp"

#include "../Objects/Stable/CrossRoadImages.hpp"
#include "../Objects/Stable/BossRoomImages.hpp"
#include "../Objects/Stable/Central.hpp"

#include <iostream>
#include <ostream>
#include <sstream>

EditingScene::EditingScene() noexcept
{
	positionSetting = false;
	layer = 0;
	isTabClicked = false;
	collisionSetting = false;
}

void EditingScene::Init()
{
	backboard.setPosition(0.f, 0.f);
	backboard.setFillColor(Color(51,51,51));
	//backboard.setFillColor(Color(0, 0, 0));
	backboard.setSize(Vector2f(2000.f, 1000.f));

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
	
	colliderButton = new button("collider", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 50.f), Vector2f(100.f, 25.f));

	// 버튼 생성
	groundButton = new button("ground", Vector2f(ViewManager::GetInstance().GetResolution().x-100.f, 100.f), Vector2f(100.f, 25.f));
	layeredButton = new button("layered", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 130.f), Vector2f(100.f, 25.f));
	buildingButton = new button("building", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 160.f), Vector2f(100.f, 25.f));
	backgroundButton = new button("bg", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 190.f), Vector2f(100.f, 25.f));
	graveCrossButton = new button("graveCross", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 220.f), Vector2f(100.f, 25.f));
	extraButton = new button("extra", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 250.f), Vector2f(100.f, 25.f));
	benchButton = new button("bench", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 280.f), Vector2f(100.f, 25.f));
	portalButton = new button("portal", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 310.f), Vector2f(100.f, 25.f));
	platformButton = new button("platform", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 340.f), Vector2f(100.f, 25.f));
	thornButton = new button("thorn", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 370.f), Vector2f(100.f, 25.f));
	wallButton = new button("wall", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 580.f), Vector2f(100.f, 25.f));
	elevButton = new button("elev", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 790.f), Vector2f(100.f, 25.f));
	
	// kings pass
	kp_groundButton = new button("kpGround", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 400.f), Vector2f(100.f, 25.f));
	kp_doorButton = new button("kpDoor", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 430.f), Vector2f(100.f, 25.f));
	kp_imagesButton = new button("kpImages", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 460.f), Vector2f(100.f, 25.f));
	kp_bgButton = new button("kpBG", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 490.f), Vector2f(100.f, 25.f));
	kp_wallButton = new button("kpWall", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 520.f), Vector2f(100.f, 25.f));
	kp_objectButton = new button("kpObjects", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 550.f), Vector2f(100.f, 25.f));

	// crossRoad
	cr_groundButton = new button("crGround", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 610.f), Vector2f(100.f, 25.f));
	cr_imagesButton = new button("crImages", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 640.f), Vector2f(100.f, 25.f));
	cr_bgButton = new button("crBG", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 670.f), Vector2f(100.f, 25.f));
	cr_roofButton = new button("crRoof", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 700.f), Vector2f(100.f, 25.f));
	cr_wallButton = new button("crWall", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 730.f), Vector2f(100.f, 25.f));
	cr_objectButton = new button("crObjects", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 760.f), Vector2f(100.f, 25.f));

	// bossRoom
	bossRoomButton = new button("bossRoom", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 820.f), Vector2f(100.f, 25.f));
	centralButton = new button("central", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 850.f), Vector2f(100.f, 25.f));

	saveButton = new button("Save", Vector2f(ViewManager::GetInstance().GetResolution().x - 300.f, 950.f), Vector2f(90.f, 30.f));
	loadButton = new button("Load", Vector2f(ViewManager::GetInstance().GetResolution().x - 200.f, 950.f), Vector2f(90.f, 30.f));
	exitButton = new button("Exit", Vector2f(ViewManager::GetInstance().GetResolution().x - 100.f, 950.f), Vector2f(90.f, 30.f));

	objectButtons.push_back(colliderButton);

	objectButtons.push_back(groundButton);
	objectButtons.push_back(layeredButton);
	objectButtons.push_back(buildingButton);
	objectButtons.push_back(backgroundButton);
	objectButtons.push_back(graveCrossButton);
	objectButtons.push_back(extraButton);
	objectButtons.push_back(benchButton);
	objectButtons.push_back(portalButton);
	objectButtons.push_back(platformButton);
	objectButtons.push_back(thornButton);
	objectButtons.push_back(wallButton);
	objectButtons.push_back(elevButton);

	objectButtons.push_back(kp_groundButton);
	objectButtons.push_back(kp_doorButton);
	objectButtons.push_back(kp_imagesButton);
	objectButtons.push_back(kp_bgButton);
	objectButtons.push_back(kp_wallButton);
	objectButtons.push_back(kp_objectButton);

	objectButtons.push_back(cr_groundButton);
	objectButtons.push_back(cr_imagesButton);
	objectButtons.push_back(cr_bgButton);
	objectButtons.push_back(cr_roofButton);
	objectButtons.push_back(cr_wallButton);
	objectButtons.push_back(cr_objectButton);

	objectButtons.push_back(bossRoomButton);
	objectButtons.push_back(centralButton);

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


	SetCollider();
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
		else if (exitButton->IsButtonClicked())
		{
			SceneManager::GetInstance().Load(L"Title");
			return;
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

	if (this->object != nullptr)
	{
		if (InputManager::GetInstance().GetKeyDown(Keyboard::Z))
		{
			this->object->GetSprite().setRotation(this->object->GetSprite().getRotation() -10);
		}
		else if (InputManager::GetInstance().GetKeyDown(Keyboard::C))
		{
			this->object->GetSprite().setRotation(this->object->GetSprite().getRotation() + 10);
		}
	}
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
			if (((*it)->GetLayer() == i))
			{
				(*it)->Render(window);
			}
		}
	}

	if (nullptr != collider)
	{
		collider->Render(window);
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
		else if (selectName == "wall")
		{
			temp = new Wall();
		}
		else if (selectName == "kpGround")
		{
			temp = new KingsPassGround();
		}
		else if (selectName == "kpDoor")
		{
			temp = new Door();
		}
		else if (selectName == "kpImages")
		{
			temp = new KingsPassImages();
		}
		else if (selectName == "kpBG")
		{
			temp = new KingsPassBG();
		}
		else if (selectName == "kpWall")
		{
			temp = new KingsPassWall();
		}
		else if (selectName == "kpObjects")
		{
			temp = new KingsPassObjects();
		}
		else if (selectName == "platform")
		{
			temp = new Platform();
		}
		else if (selectName == "elev")
		{
			temp = new CrossRoadElev();
		}
		else if (selectName == "bossRoom")
		{
			temp = new BossRoomImages();
		}
		else if (selectName == "crGround")
		{
			temp = new CrossRoadGround();
		}
		else if (selectName == "crImages")
		{
			temp = new CrossRoadImages();
		}
		else if (selectName == "crBG")
		{
			temp = new CrossRoadBG();
		}
		else if (selectName == "crRoof")
		{
			temp = new CrossRoadRoof();
		}
		else if (selectName == "crWall")
		{
			temp = new CrossRoadWall();
		}
		else if (selectName == "crObjects")
		{
			temp = new CrossRoadObjects();
		}
		else if (selectName == "central")
		{
			temp = new Central();
		}
		else if (selectName == "thorn")
		{
			temp = new thorn();
			stringstream ss;
			ss << 1;
			button* objectName = new button(ss.str(), Vector2f(ViewManager::GetInstance().GetResolution().x - 175.f, 10.f), Vector2f(50.f, 25.f));
			ImageIndexList.push_back(objectName);
			return;
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
		else if (selectName == "platform")
		{
			this->object = new Platform(inputImageIdx);
		}
		else if (selectName == "elev")
		{
			this->object = new CrossRoadElev(inputImageIdx);
		}
		else if (selectName == "thorn")
		{
			this->object = new thorn();
		}
		else if (selectName == "wall")
		{
			this->object = new Wall(inputImageIdx);
		}
		else if (selectName == "kpGround")
		{
			this->object = new KingsPassGround(inputImageIdx);
		}
		else if (selectName == "kpDoor")
		{
			this->object = new Door(inputImageIdx);
		}
		else if (selectName == "kpImages")
		{
			this->object = new KingsPassImages(inputImageIdx);
		}
		else if (selectName == "kpBG")
		{
			this->object = new KingsPassBG(inputImageIdx);
		}
		else if (selectName == "kpWall")
		{
			this->object = new KingsPassWall(inputImageIdx);
		}
		else if (selectName == "kpObjects")
		{
			this->object = new KingsPassObjects(inputImageIdx);
		}
		else if (selectName == "crGround")
		{
			this->object = new CrossRoadGround(inputImageIdx);
		}
		else if (selectName == "crImages")
		{
			this->object = new CrossRoadImages(inputImageIdx);
		}
		else if (selectName == "crBG")
		{
			this->object = new CrossRoadBG(inputImageIdx);
		}
		else if (selectName == "crRoof")
		{
			this->object = new CrossRoadRoof(inputImageIdx);
		}
		else if (selectName == "crWall")
		{
			this->object = new CrossRoadWall(inputImageIdx);
		}
		else if (selectName == "crObjects")
		{
			this->object = new CrossRoadObjects(inputImageIdx);
		}
		else if (selectName == "bossRoom")
		{
			this->object = new BossRoomImages(inputImageIdx);
		}
		else if (selectName == "central")
		{
			this->object = new Central(inputImageIdx);
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
			object = nullptr;
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
		ViewManager::GetInstance().GetMainView().move(2.f, 0.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Left)
		|| InputManager::GetInstance().GetKey(Keyboard::A))
	{
		ViewManager::GetInstance().GetMainView().move(-2.f, 0.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Up)
		|| InputManager::GetInstance().GetKey(Keyboard::W))
	{
		ViewManager::GetInstance().GetMainView().move(0.f, -2.f);
	}
	else if (InputManager::GetInstance().GetKey(Keyboard::Down)
		|| InputManager::GetInstance().GetKey(Keyboard::S))
	{
		ViewManager::GetInstance().GetMainView().move(0.f, 2.f);
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
		if (!InputManager::GetInstance().GetKey(Keyboard::T))
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
}

void EditingScene::SetManual()
{
	manualText.setPosition(static_cast<Vector2f>(InputManager::GetInstance().GetMousePosition()));
	
	if(positionSetting)
	{
		manualText.setString(L"Z - rotate(-10)\nC - rotate(+10)\nRIGHT - undo\nSPACE - put\nBACK SPACE - delete");
	}
	else if (collisionSetting)
	{
		manualText.setString(L"BUTTON UP - set size\nSPACE - put");
	}
	else
	{
		manualText.setString(L"LEFT - select\nTAB - info\nT+LEFT - collider\nDELETE - del collider");
	}
}

void EditingScene::Save()
{
	ofstream dataFile;
	dataFile.open("data_tables/maps/CrossRoad_map_data.csv");
	if (dataFile.fail())
	{
		cout << "File load Failed" << endl;
		return;
	}
	dataFile << "NAME,INDEX,LAYER,X,Y,ROTATE,SIZE_X,SIZE_Y\n";
	for (int i = 0; i < objects.size(); ++i)
	{
		dataFile << objects[i]->GetName() << "," << objects[i]->GetImageIdx()
			<< "," << objects[i]->GetLayer() << "," << objects[i]->GetPosition().x
			<< "," << objects[i]->GetPosition().y << "," << objects[i]->GetSprite().getRotation()
			<< "," << objects[i]->GetRectangleShape().getSize().x << "," << objects[i]->GetRectangleShape().getSize().y << endl;
	}
	cout << "Save Complete File" << endl;
	dataFile.close();
}

void EditingScene::Load()
{
	rapidcsv::Document dataFile("data_tables/maps/CrossRoad_map_data.csv");

	vector<string> colName = dataFile.GetColumn<string>("NAME");
	vector<int> colIndex = dataFile.GetColumn<int>("INDEX");
	vector<int> colLayer = dataFile.GetColumn<int>("LAYER");
	vector<float> colX = dataFile.GetColumn<float>("X");
	vector<float> colY = dataFile.GetColumn<float>("Y");
	vector<float> colRotate = dataFile.GetColumn<float>("ROTATE");
	vector<float> colSize_x = dataFile.GetColumn<float>("SIZE_X");
	vector<float> colSize_y = dataFile.GetColumn<float>("SIZE_Y");

	int totalObjects = colName.size();
	for (int i = 0; i < totalObjects; ++i)
	{
		MapData data;
		data.name = colName[i];
		data.index = colIndex[i];
		data.layer = colLayer[i];
		data.x = colX[i];
		data.y = colY[i];
		data.rotate = colRotate[i];
		data.size_x = colSize_x[i];
		data.size_y = colSize_y[i];

		if (data.name == "collider")
		{
			LoadCollision(data);
		}
		else
		{
			AddObject(data);
		}
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
	else if (data.name == "platform")
	{
		this->object = new Platform(data.index);
	}
	else if (data.name == "elev")
	{
		this->object = new CrossRoadElev(data.index);
	}
	else if (data.name == "thorn")
	{
		this->object = new thorn();
	}
	else if (data.name == "wall")
	{
		this->object = new Wall(data.index);
	}
	else if (data.name == "kpGround")
	{
		this->object = new KingsPassGround(data.index);
	}
	else if (data.name == "kpDoor")
	{
		this->object = new Door(data.index);
	}
	else if (data.name == "kpImages")
	{
		this->object = new KingsPassImages(data.index);
	}
	else if (data.name == "kpBG")
	{
		this->object = new KingsPassBG(data.index);
	}
	else if (data.name == "kpWall")
	{
		this->object = new KingsPassWall(data.index);
	}
	else if (data.name == "kpObjects")
	{
		this->object = new KingsPassObjects(data.index);
	}
	else if (data.name == "crGround")
	{
		this->object = new CrossRoadGround(data.index);
	}
	else if (data.name == "crImages")
	{
		this->object = new CrossRoadImages(data.index);
	}
	else if (data.name == "crBG")
	{
		this->object = new CrossRoadBG(data.index);
	}
	else if (data.name == "crRoof")
	{
		this->object = new CrossRoadRoof(data.index);
	}
	else if (data.name == "crWall")
	{
		this->object = new CrossRoadWall(data.index);
	}
	else if (data.name == "crObjects")
	{
		this->object = new CrossRoadObjects(data.index);
	}
	else if (data.name == "bossRoom")
	{
		this->object = new BossRoomImages(data.index);
	}
	else if (data.name == "central")
	{
		this->object = new Central(data.index);
	}
	this->object->SetLayer(data.layer);
	this->object->SetPosition(Vector2f(data.x, data.y));
	this->object->SetOriginCenter();
	this->object->GetSprite().setRotation(data.rotate);
}

void EditingScene::LoadCollision(MapData& data)
{
	this->object = new Collider(Vector2f(data.size_x, data.size_y), Vector2f(data.x, data.y));
}

void EditingScene::SetCollider()
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if ((*it)->CompareTag(TAG::COLLIDER) &&
			(*it)->GetRectangleShape().getGlobalBounds().contains(InputManager::GetInstance().GetMouseWorldPosition()))
		{
			if (InputManager::GetInstance().GetKeyDown(Keyboard::Delete))
			{
				objects.erase(it);
				break;
			}
		}
	}

	if (InputManager::GetInstance().GetKey(Keyboard::T))
	{
		// 콜라이더의 시작점이 될 좌상점의 위치를 입력받음
		if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Left))
		{
			collisionSetting = true;
			collider = new Collider();
			startPos = InputManager::GetInstance().GetMouseWorldPosition();

			collider->GetShape().setOutlineThickness(2.f);
			collider->GetShape().setOutlineColor(Color::Green);
			collider->GetShape().setFillColor(Color(0, 0, 0, 0));
			collider->GetShape().setPosition(startPos);
		}
		if (InputManager::GetInstance().GetMouseButton(Mouse::Left))
		{
			endPos = InputManager::GetInstance().GetMouseWorldPosition();
			collider->GetShape().setSize(Vector2f(endPos - startPos));
		}
		if (InputManager::GetInstance().GetMouseButtonUp(Mouse::Left))
		{
			// 버튼이 떼진 위치가 우하점이 됨
			endPos = InputManager::GetInstance().GetMouseWorldPosition();
			// 좌상점, 우하점이 정해졌을 때의 크기로 rectangleShape의 크기 조절
			collider->GetShape().setSize(Vector2f(endPos - startPos));
		}
	}
	// 스페이스나 결정 입력을 받으면 해당 크기로 결정됨
	// 취소하면 그냥 지워줌?
	if (collider != nullptr && InputManager::GetInstance().GetKeyDown(Keyboard::Space))
	{
		collider->SetPosition(startPos);
		objects.push_back(collider);

		collider = nullptr;
		delete collider;

		collisionSetting = false;
	}
	// 확인이 되면 colliders에 저장
}
