#pragma once
#include <unordered_map>
#include <string>
#include "../Utils/button.hpp"

using namespace sf;
using namespace std;

class textureListBoxUI
{
private:
	unordered_map<string, Texture*> textureMap;
	unordered_map<string, Sprite*> spriteMap;

	RectangleShape ListBox;// ��ư�� Ŭ���Ǹ� ������ �ؽ�ó ��� �ڽ�
	button* closeButton;
public:
	textureListBoxUI();
	~textureListBoxUI();

	void Update(bool* isOpen);
	void Render(RenderWindow& window);
	void Release();
};

