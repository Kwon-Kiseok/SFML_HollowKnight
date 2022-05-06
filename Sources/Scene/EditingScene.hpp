#pragma once
#include "Scene.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include "../Utils/button.hpp"
#include "../Objects/GameObject.hpp"

using namespace sf;
using namespace std;
// ¸Ê ¿¡µðÆÃÀ» ÇÒ ¾À
class EditingScene : public Scene
{
private:
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

	bool ClikedgroundButton;

public:
	EditingScene() noexcept;
	~EditingScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;
	void MoveView();
};

