#pragma once
#include "Scene.hpp"

using namespace sf;
class TitleScene : public Scene
{
private:
	float Cursor_selectY = 600.f;

	Texture textureBackGround;
	Sprite spriteBackGround;

	Texture textureTitle;
	Sprite spriteTitle;

	Texture textureCursor;
	Sprite spriteCursor;

	Font fontArial;
	Text textPlay;
	Text textEditor;
	Text textExit;

public:
	TitleScene() {}
	virtual ~TitleScene() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Release() override;
};

