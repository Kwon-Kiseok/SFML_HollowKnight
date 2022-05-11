#pragma once
#include "Scene.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include "../Utils/button.hpp"
#include "../Objects/GameObject.hpp"
#include "../Maps/Map.hpp"

#define MAX_LAYER 10
#define MIN_LAYER 0

using namespace sf;
using namespace std;
// ¸Ê ¿¡µðÆÃÀ» ÇÒ ¾À
class Player;
class EditingScene : public Scene
{
private:
	RectangleShape backboard;

	Font font;
	Text currentCursorPos;
	string editData;

	string selectName;
	string inputLayer;
	string inputIndex;

	int layer;
	int inputImageIdx;

	int count = 0;
	bool positionSetting;

	vector<GameObject*> objects;
	GameObject* object;

	// Ãæµ¹Ã¼
	vector<RectangleShape*> colliders;
	RectangleShape* collider;
	button* colliderButton;

	Vector2f startPos;	// ÁÂ»óÁ¡
	Vector2f endPos;	// ¿ìÇÏÁ¡

	// tut
	button* groundButton;		// ¹Ù´Ú
	button* layeredButton;		// 
	button* buildingButton;		//
	button* backgroundButton;	// µÞ ¹è°æ
	button* graveCrossButton;
	button* extraButton;
	button* benchButton;
	button* portalButton;		// Æ÷Å»

	button* platformButton;
	button* thornButton;
	button* wallButton;

	button* elevButton;			// ¿¤¸®º£ÀÌÅÍ

	// kingsPass
	button* kp_groundButton;
	button* kp_doorButton;
	button* kp_imagesButton;
	button* kp_bgButton;
	button* kp_wallButton;
	button* kp_objectButton;

	// crossRoad
	button* cr_groundButton;
	button* cr_imagesButton;
	button* cr_bgButton;
	button* cr_roofButton;
	button* cr_wallButton;
	button* cr_objectButton;

	// bossRoom
	button* bossRoomButton;
	button* centralButton;

	//
	button* saveButton;
	button* loadButton;
	button* exitButton;

	vector<button*> objectButtons;
	vector<button*> ImageIndexList;
	bool checkImageIdx;
	Text layerIndicator;
	button* plusLayerButton;
	button* minusLayerButton;
	button* confirmLayerButton;

	vector<Text*> objectStatuses;
	string stringStatus;
	bool isTabClicked;

	Vector2f prevPos;
	bool selectObject;
	Text manualText;

public:
	EditingScene() noexcept;
	~EditingScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	void ObjectSeleted(button& button);
	void OpenImageIndex(button& btn);
	void SetImageIndex();
	void SetLayer();
	void SetObjectsPosition();
	void MoveView();
	void CursorPosView();
	void ViewObjectsInfos();

	void ClickObject();
	void SetManual();

	void Save();
	void Load();
	void AddObject(MapData& data);

	void SetCollider();
};

