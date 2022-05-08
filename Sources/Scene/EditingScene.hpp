#pragma once
#include "Scene.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include "../Utils/button.hpp"
#include "../Objects/GameObject.hpp"

#define MAX_LAYER 10
#define MIN_LAYER 0

using namespace sf;
using namespace std;
// ¸Ê ¿¡µðÆÃÀ» ÇÒ ¾À
class EditingScene : public Scene
{
private:
	RectangleShape backboard;

	Font font;
	Text currentCursorPos;
	string cursorData;

	string selectName;
	string inputLayer;
	string inputIndex;

	int layer;
	int inputImageIdx;

	int count = 0;
	bool positionSetting;

	vector<GameObject*> objects;

	GameObject* object;

	button* groundButton;		// ¹Ù´Ú
	button* layeredButton;		// 
	button* buildingButton;		//
	button* backgroundButton;	// µÞ ¹è°æ

	button* saveButton;
	button* exitButton;

	vector<button*> buttons;

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
};

