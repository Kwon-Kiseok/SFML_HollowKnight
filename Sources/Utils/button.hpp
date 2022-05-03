#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum class Button_state
{
	normal = 0,
	hovered,
	clicked,
};

class button
{
private:
	Vector2f position;
	RectangleShape buttonShape;
	Text text;
	Font font;
	Button_state state;

	bool isClick;
public:
	button();
	button(string text, Vector2f pos, Vector2f size);
	~button();

	void update();
	void Click(bool isHovered);
	void draw(RenderWindow& window);
	bool IsButtonClicked();
	void ResetIsClicked();
};