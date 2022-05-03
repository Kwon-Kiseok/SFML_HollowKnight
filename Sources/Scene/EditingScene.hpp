#pragma once
#include "Scene.hpp"
#include <unordered_map>
#include <string>
#include "../Utils/button.hpp"
#include "../Utils/textureListBoxUI.hpp"
using namespace sf;
using namespace std;
// 맵 에디팅을 할 씬
class EditingScene : public Scene
{
private:
	unordered_map<string, Texture*> textureMap;
	unordered_map<int, Sprite*> spriteMap;
	int clickCount;

	button* textureLoadButton;	// 텍스쳐 로드 버튼
	bool isOpenTextureWindow; // 텍스처 윈도우가 열려있는지

	textureListBoxUI* listBoxUI;

public:
	EditingScene() noexcept = default;
	~EditingScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;
};

