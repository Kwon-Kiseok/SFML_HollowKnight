#pragma once
#include <SFML/Graphics.hpp>

///
/// Utility성 편의기능들을 불러오기 위한 클래스
/// staitc 함수들을 가져 필요한 곳에서 사용할 수 있다.
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

