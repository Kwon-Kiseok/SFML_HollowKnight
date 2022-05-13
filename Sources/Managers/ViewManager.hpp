#pragma once
#include "../include/Singleton.hpp"
#include <SFML/Graphics.hpp>
#include "../Player/Player.hpp"

using namespace sf;

class ViewManager : public Singleton<ViewManager>
{
private:
	View* mainView = nullptr;
	View* uiView = nullptr;
	Vector2i resolution;
	float shakeTime = 2.f;
	bool isDamaged = false;
	RectangleShape damagedDimmed;

public:
	ViewManager() noexcept = default;
	~ViewManager() noexcept = default;

	void Init();
	void ClearView();
	void CameraShake(float dt);
	void turnoffDimmed();
	View& GetMainView() const;
	View& GetUiView() const;
	Vector2i& GetResolution();
	void draw(RenderWindow& window);

	// view �ٿ�� ó�� ���� move �Լ��� ���� �ٿ��,,,, >> �� ��ü ������ �޾ӿ;� �� ����
	void TracePlayer(Player& player, Vector2f min_size, Vector2f max_size);
};

