#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis
{
	Horizontal,		// �����Է�
	Vertical,		// �����Է�
};

struct AxisInfo
{
	Axis axis;							// ���� �Է� ��
	list<Keyboard::Key> positiveKeys;	// �࿡ ��� ���� ������ Ű
	list<Keyboard::Key> negativeKeys;	// �࿡ ���� ���� ������ Ű

	float sensi = 0;		// ���� ��ǥ ���� ���� �̵��ϴ� �ӵ�(�ʴ� ����)
	float limit = 0;		//
	float value = 0;		// -1.0 ~ 1.0
};

class InputManager : public Singleton<InputManager>
{
private:
	static map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;	// �������� ���� �������� Ű
	static list<Keyboard::Key> keys;		// �������ִ� ������ ���� Ű
	static list<Keyboard::Key> upKeys;		// �������� ���� �������� Ű

	static list<Mouse::Button> downButtons; // �������� ���� �������� ��ư
	static list<Mouse::Button> buttons;		// �������ִ� ������ ���� ��ư
	static list<Mouse::Button> upButtons;	// �������� ���� �������� ��ư

	static Vector2i mousePosition;			// ���콺�� ��������� ��ġ
	static Vector2f mouseWorldPosition;		// ���콺�� ���� ���� ��ġ

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
	/// ���� ���� ���� float ��ȯ
	/// </summary>
	float GetAxis(Axis axis) noexcept;

	float GetCurrentZoom() noexcept;

	/// <summary>
	/// ���� Ű���� Ű�� �࿡ ���� ���� ������, ���� ������ ��ȯ -1, 0, 1
	/// </summary>
	int GetAxisRaw(const list<Keyboard::Key>& positive, const list<Keyboard::Key>& negative) noexcept;
	int GetAxisRaw(Axis axis) noexcept;

	/// <summary>
	/// Ű���� Ű�� ������ ���� �������� �˻��ϴ� �Լ�
	/// </summary>
	bool GetKeyDown(Keyboard::Key key) noexcept;
	/// <summary>
	/// Ű���� Ű�� �������ִ� �������� �˻��ϴ� �Լ�
	/// </summary>
	bool GetKey(Keyboard::Key key) noexcept;
	/// <summary>
	/// Ű���� Ű�� �������� ���� �������� �˻��ϴ� �Լ�
	/// </summary>
	bool GetKeyUp(Keyboard::Key key) noexcept;

	/// <summary>
	/// ���콺�� ����ũ�鿡���� ��ġ Vector2i ��ȯ
	/// </summary>
	Vector2i GetMousePosition() noexcept;
	/// <summary>
	/// ���콺�� ���忡���� ��ġ Vector2f ��ȯ
	/// </summary>
	Vector2f GetMouseWorldPosition() noexcept;

	/// <summary>
	/// ���콺 ��ư�� ������ ���� �������� �˻��ϴ� �Լ�
	/// </summary>
	bool GetMouseButtonDown(Mouse::Button button) noexcept;
	/// <summary>
	/// ���콺 ��ư�� �������ִ� �������� �˻��ϴ� �Լ�
	/// </summary>
	bool GetMouseButton(Mouse::Button button) noexcept;
	/// <summary>
	/// ���콺 ��ư�� �������� ���� �������� �˻��ϴ� �Լ�
	/// </summary>
	bool GetMouseButtonUp(Mouse::Button button) noexcept;
};

