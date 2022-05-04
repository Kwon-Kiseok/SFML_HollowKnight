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
	string id;
	RectangleShape ListBox;// ��ư�� Ŭ���Ǹ� ������ �ؽ�ó ��� �ڽ�
	button* closeButton;

	button* testRockButton;
	bool isActive;
	bool isDrop;

	button* testPoleButton;
public:
	textureListBoxUI();
	~textureListBoxUI();

	void Init();
	void AddTexture(string path, string id, Vector2f pos);
	void Update(bool* isOpen);
	void Render(RenderWindow& window);
	void Release();

	Sprite& GetDropImage();
	bool GetIsDrop();
	void ResetIsDrop();
	string& GetId();
};

