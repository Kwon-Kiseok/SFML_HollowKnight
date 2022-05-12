#pragma once
#include <SFML/Graphics.hpp>

///
/// Utility�� ���Ǳ�ɵ��� �ҷ����� ���� Ŭ����
/// staitc �Լ����� ���� �ʿ��� ������ ����� �� �ִ�.
///
using namespace sf;

enum class Pivots
{
	LT, CT, RT,
	LC, CC, RC,
	LB, CB, RB,
};

class Utility
{
public:
	static void SetOrigin(Text& text, Pivots preset);
	static void SetOrigin(Sprite& sprite, Pivots preset);
	static void SetOrigin(Shape& shape, Pivots preset);
	static void SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset);

	static int Random(int min, int max);

	static float GetLength(const Vector2f& vector);
	static Vector2f Normalize(Vector2f vector);
	static float GetAngle(const Vector2f& from, const Vector2f& to);

	static Pivots CollisionDir(FloatRect start, FloatRect comp);
};

