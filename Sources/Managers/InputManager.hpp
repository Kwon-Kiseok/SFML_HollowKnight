#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis
{
	Horizontal,		// 가로입력
	Vertical,		// 세로입력
};

struct AxisInfo
{
	Axis axis;							// 가상 입력 축
	list<Keyboard::Key> positiveKeys;	// 축에 양수 값을 보내는 키
	list<Keyboard::Key> negativeKeys;	// 축에 음수 값을 보내는 키

	float sensi = 0;		// 축이 목표 값을 향해 이동하는 속도(초당 단위)
	float limit = 0;		//
	float value = 0;		// -1.0 ~ 1.0
};

class InputManager : public Singleton<InputManager>
{
private:
	static map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;	// 눌러지는 순간 프레임의 키
	static list<Keyboard::Key> keys;		// 눌려져있는 프레임 동안 키
	static list<Keyboard::Key> upKeys;		// 떼어지는 순간 프레임의 키

	static list<Mouse::Button> downButtons; // 눌러지는 순간 프레임의 버튼
	static list<Mouse::Button> buttons;		// 눌려져있는 프레임 동안 버튼
	static list<Mouse::Button> upButtons;	// 떼어지는 순간 프레임의 버튼

	static Vector2i mousePosition;			// 마우스의 윈도우상의 위치
	static Vector2f mouseWorldPosition;		// 마우스의 월드 상의 위치

	const float zoomAmount{ 1.02f };
	float currentZoom = 1.0f;
public:
	InputManager() noexcept = default;
	~InputManager() noexcept = default;

	void HorizontalInit();
	void VerticalInit();

public:
	void Init() noexcept;
	void ProcessInput(const Event& event);
	void Update(float dt, RenderWindow& window, View& worldView);
	void ClearInput() noexcept;

	/// <summary>
	/// 현재 축의 값을 float 반환
	/// </summary>
	float GetAxis(Axis axis) noexcept;

	float GetCurrentZoom() noexcept;

	/// <summary>
	/// 눌린 키보드 키가 축에 대해 양의 값인지, 음의 값인지 반환 -1, 0, 1
	/// </summary>
	int GetAxisRaw(const list<Keyboard::Key>& positive, const list<Keyboard::Key>& negative) noexcept;
	int GetAxisRaw(Axis axis) noexcept;

	/// <summary>
	/// 키보드 키가 눌리는 순간 프레임을 검사하는 함수
	/// </summary>
	bool GetKeyDown(Keyboard::Key key) noexcept;
	/// <summary>
	/// 키보드 키가 눌려져있는 프레임을 검사하는 함수
	/// </summary>
	bool GetKey(Keyboard::Key key) noexcept;
	/// <summary>
	/// 키보드 키가 떼어지는 순간 프레임을 검사하는 함수
	/// </summary>
	bool GetKeyUp(Keyboard::Key key) noexcept;

	/// <summary>
	/// 마우스의 데스크톱에서의 위치 Vector2i 반환
	/// </summary>
	Vector2i GetMousePosition() noexcept;
	/// <summary>
	/// 마우스의 월드에서의 위치 Vector2f 반환
	/// </summary>
	Vector2f GetMouseWorldPosition() noexcept;

	/// <summary>
	/// 마우스 버튼이 눌리는 순간 프레임을 검사하는 함수
	/// </summary>
	bool GetMouseButtonDown(Mouse::Button button) noexcept;
	/// <summary>
	/// 마우스 버튼이 눌려져있는 프레임을 검사하는 함수
	/// </summary>
	bool GetMouseButton(Mouse::Button button) noexcept;
	/// <summary>
	/// 마우스 버튼이 떼어지는 순간 프레임을 검사하는 함수
	/// </summary>
	bool GetMouseButtonUp(Mouse::Button button) noexcept;
};

