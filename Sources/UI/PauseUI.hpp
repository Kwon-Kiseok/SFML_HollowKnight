#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/button.hpp"
#include <unordered_map>
#include <string>

using namespace sf;
using namespace std;

class PauseUI
{
private:
	unordered_map<wstring, button*> pauseButtons;

public:
	PauseUI();
	~PauseUI();

	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);
	void Release();
};

