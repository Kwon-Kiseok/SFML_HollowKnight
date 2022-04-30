#include "ViewManager.hpp"
#include "../Utils/Utility.hpp"

void ViewManager::Init()
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	mainView = new View(FloatRect(0.f, 0.f, resolution.x, resolution.y));
	uiView = new View(FloatRect(0.f, 0.f, resolution.x, resolution.y));

	damagedDimmed.setSize(uiView->getSize());
	damagedDimmed.setOrigin(0, 0);
	damagedDimmed.setFillColor(Color(220, 0, 0, 50));
}

void ViewManager::ClearView()
{
	delete mainView;
	mainView = nullptr;

	delete uiView;
	uiView = nullptr;
}

View& ViewManager::GetMainView() const
{
	return *mainView;
}

void ViewManager::CameraShake(float dt)
{
	while (shakeTime > 0)
	{
		isDamaged = true;
		mainView->move(Utility::Random(-3.f, 3.f), Utility::Random(-3.f, 3.f));
		shakeTime -= dt;
	}
	shakeTime = 2.f;
}

View& ViewManager::GetUiView() const
{
	return *uiView;
}

Vector2i& ViewManager::GetResolution()
{
	return resolution;
}

void ViewManager::turnoffDimmed()
{
	if (isDamaged)
		isDamaged = false;
}

void ViewManager::draw(RenderWindow& window)
{
	if (isDamaged)
		window.draw(damagedDimmed);
}
