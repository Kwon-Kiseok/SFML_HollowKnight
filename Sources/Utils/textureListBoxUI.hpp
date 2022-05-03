#pragma once
#include <unordered_map>
#include <string>
#include "../Utils/button.hpp"

using namespace sf;
using namespace std;

class textureListBoxUI
{
private:
	Texture texture;
	unordered_map<string, Sprite*> spriteMap;

	RectangleShape ListBox;// 버튼이 클릭되면 나오는 텍스처 목록 박스
	button* closeButton;

	button* testRockButton;
	bool isActive;
	bool isDrop;
public:
	textureListBoxUI();
	~textureListBoxUI();

	void Init();
	void AddTexture(string path, Vector2f pos);
	void Update(bool* isOpen);
	void Render(RenderWindow& window);
	void Release();

	Sprite& GetDropImage();
	bool GetIsDrop();
	void ResetIsDrop();
};

