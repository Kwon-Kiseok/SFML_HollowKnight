#include "InputManager.hpp"
#include "ViewManager.hpp"
#include "SceneManager.hpp"
#include <algorithm>
#include <cmath>


map<Axis, AxisInfo> InputManager::mapAxis;

list<Keyboard::Key> InputManager::downKeys;
list<Keyboard::Key> InputManager::keys;
list<Keyboard::Key> InputManager::upKeys;

list<Mouse::Button> InputManager::downButtons;
list<Mouse::Button> InputManager::buttons;
list<Mouse::Button> InputManager::upButtons;

Vector2i InputManager::mousePosition;
Vector2f InputManager::mouseWorldPosition;

void InputManager::Init() noexcept
{
	mapAxis.clear();

	AxisInfo info;
	// Horizontal
	info.axis = Axis::Horizontal;
	info.sensi = 1.f;
	info.limit = 0.05f;
	info.value = 0.f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::D);
	info.positiveKeys.push_back(Keyboard::Right);

	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::A);
	info.negativeKeys.push_back(Keyboard::Left);
	mapAxis[info.axis] = info;

	// Vertical
	info.axis = Axis::Vertical;
	info.sensi = 1.f;
	info.limit = 0.05f;
	info.value = 0.f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::S);
	info.positiveKeys.push_back(Keyboard::Down);

	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::W);
	info.negativeKeys.push_back(Keyboard::Up);
	mapAxis[info.axis] = info;
}

void InputManager::ClearInput() noexcept
{
	downKeys.clear();
	upKeys.clear();
	downButtons.clear();
	upButtons.clear();
}

void InputManager::ProcessInput(const Event& event)
{
	// event.key.code
	switch (event.type)
	{
	case Event::KeyPressed:
		if (!GetKey(event.key.code))
		{
			downKeys.push_back(event.key.code);
			keys.push_back(event.key.code);
		}
		break;
	case Event::KeyReleased:
		keys.remove(event.key.code);
		upKeys.push_back(event.key.code);
		break;
	case Event::MouseButtonPressed:
	{
		downButtons.push_back(event.mouseButton.button);
		buttons.push_back(event.mouseButton.button);
	}
		break;
	case Event::MouseButtonReleased:
	{
		buttons.remove(event.mouseButton.button);
		upButtons.push_back(event.mouseButton.button);
	}
		break;
	case Event::MouseWheelScrolled:
	{
		// 에디터 씬에서만
		if (SceneManager::GetInstance().GetScenes().find(L"Editor")->second
			== SceneManager::GetInstance().GetCurrent())
		{
			if (event.mouseWheelScroll.delta >= 1)
			{
				ViewManager::GetInstance().GetMainView().zoom(1.f / zoomAmount);
				currentZoom /= zoomAmount;
			}
			if (event.mouseWheelScroll.delta <= -1)
			{
				ViewManager::GetInstance().GetMainView().zoom(1.02f);
				currentZoom *= 1.02f;
			}
		}
	}
		break;
	default:
		break;
	}
}

void InputManager::Update(float dt, RenderWindow& window, View& worldView)
{
	for (auto it = mapAxis.begin(); it != mapAxis.end(); ++it)
	{
		AxisInfo& ref = it->second;
		// 축당 하나씩 입력이 들어온다.
		int axis = GetAxisRaw(ref.axis);
		if (axis == 0)
		{
			axis = ref.value > 0 ? -1 : 1;
			if (abs(ref.value) < ref.limit)
			{
				axis = 0;
				ref.value = 0;
			}
		}

		ref.value += axis * ref.sensi * dt;
		if (ref.value > 1.f)
		{
			ref.value = 1.f;
		}
		if (ref.value < -1.f)
		{
			ref.value = -1.f;
		}
	}

	mousePosition = Mouse::getPosition();
	mouseWorldPosition = window.mapPixelToCoords(mousePosition, worldView);
}

float InputManager::GetAxis(Axis axis) noexcept
{
	if (mapAxis.find(axis) != mapAxis.end())
	{
		return mapAxis[axis].value;
	}
	return 0.0f;
}

float InputManager::GetCurrentZoom() noexcept
{
	return currentZoom;
}

int InputManager::GetAxisRaw(const list<Keyboard::Key>& positivie, const list<Keyboard::Key>& negative) noexcept
{
	int axis = 0;
	bool isPositive = false, isNegative = false;

	for (auto it = positivie.cbegin(); it != positivie.cend(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isPositive = true;
			break;
		}
	}
	for (auto it = negative.cbegin(); it != negative.cend(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isNegative = true;
			break;
		}
	}

	if (isPositive && isNegative)
	{
		axis = 0;
	}
	else if (isPositive)
	{
		axis = 1;
	}
	else if (isNegative)
	{
		axis = -1;
	}

	return axis;
}

int InputManager::GetAxisRaw(Axis axis) noexcept
{
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxisRaw(pair->second.positiveKeys, pair->second.negativeKeys);
	}
	return 0;
}

bool InputManager::GetKeyDown(Keyboard::Key key) noexcept
{
	auto it = find(downKeys.begin(), downKeys.end(), key);
	return it != downKeys.end();
}

bool InputManager::GetKey(Keyboard::Key key) noexcept
{
	auto it = find(keys.begin(), keys.end(), key);
	return it != keys.end();
}

bool InputManager::GetKeyUp(Keyboard::Key key) noexcept
{
	auto it = find(upKeys.begin(), upKeys.end(), key);
	return it != upKeys.end();
}

Vector2i InputManager::GetMousePosition() noexcept
{
	return mousePosition;
}

Vector2f InputManager::GetMouseWorldPosition() noexcept
{
	return mouseWorldPosition;
}

bool InputManager::GetMouseButtonDown(Mouse::Button button) noexcept
{
	auto it = find(downButtons.begin(), downButtons.end(), button);
	return it != downButtons.end();
}

bool InputManager::GetMouseButton(Mouse::Button button) noexcept
{
	auto it = find(buttons.begin(), buttons.end(), button);
	return it != buttons.end();
}

bool InputManager::GetMouseButtonUp(Mouse::Button button) noexcept
{
	auto it = find(upButtons.begin(), upButtons.end(), button);
	return it != upButtons.end();
}