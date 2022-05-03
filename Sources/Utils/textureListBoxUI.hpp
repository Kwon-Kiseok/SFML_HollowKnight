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

	RectangleShape ListBox;// 버튼이 클릭되면 나오는 텍스처 목록 박스
	button* closeButton;
public:
	textureListBoxUI();
	~textureListBoxUI();

	void Update(bool* isOpen);
	void Render(RenderWindow& window);
	void Release();
};

