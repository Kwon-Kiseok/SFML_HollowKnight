#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "../Animation/AnimationController.hpp"
#include "../Utils/button.hpp"

using namespace sf;
using namespace std;

class PauseUI
{
private:
	unordered_map<wstring, button*> pauseButtons;
	AnimationController animContoller;
	Sprite spritePauseTop;
	//Texture texture;
	std::map<std::string, Texture> texMap;
public:
	PauseUI();
	~PauseUI();

	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);
	void Release();

	void SetAnimation();
	AnimationController& GetAnim();
};