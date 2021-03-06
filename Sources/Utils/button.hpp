#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation/AnimationController.hpp"

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

	Texture textureCursor;
	Sprite spriteCursor_L;
	Sprite spriteCursor_R;
	bool isSelect;

	AnimationController animContoller;
	Sprite spriteButton;
	std::map<std::string, Texture> texMap;
	bool isClick;
public:
	button();
	button(string text, Vector2f pos, Vector2f size);
	~button();

	string GetText();
	void update();
	void update(float dt);
	void draw(RenderWindow& window);

	void Select(bool isHovered);
	void Click(bool isHovered);
	bool IsButtonClicked();
	void ResetIsClicked();
	bool IsButtonSelect();
	Button_state& GetButtonState();

	void SetAnimation();
};