#pragma once
#include "Scene.hpp"
#include <unordered_map>
#include <string>
#include "../Utils/button.hpp"
#include "../Utils/textureListBoxUI.hpp"
using namespace sf;
using namespace std;
// �� �������� �� ��
class EditingScene : public Scene
{
private:
	unordered_map<string, Texture*> textureMap;
	unordered_map<int, Sprite*> spriteMap;
	int clickCount;

	button* textureLoadButton;	// �ؽ��� �ε� ��ư
	bool isOpenTextureWindow; // �ؽ�ó �����찡 �����ִ���

	textureListBoxUI* listBoxUI;

public:
	EditingScene() noexcept = default;
	~EditingScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;
};

