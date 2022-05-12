#include "Utility.hpp"
#include <random>

void Utility::SetOrigin(Text& text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}

void Utility::SetOrigin(Sprite& sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}

void Utility::SetOrigin(Shape& shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}

void Utility::SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset)
{
	float wc = bounds.width * 0.5f;
	float hc = bounds.height * 0.5f;

	float w = bounds.width;
	float h = bounds.height;

	switch (preset)
	{
	case Pivots::LT:
		tr.setOrigin(0.f, 0.f);
		break;
	case Pivots::CT:
		tr.setOrigin(wc, 0.f);
		break;
	case Pivots::RT:
		tr.setOrigin(w, 0.f);
		break;
	case Pivots::LC:
		tr.setOrigin(0.f, hc);
		break;
	case Pivots::CC:
		tr.setOrigin(wc, hc);
		break;
	case Pivots::RC:
		tr.setOrigin(w, hc);
		break;
	case Pivots::LB:
		tr.setOrigin(0.f, h);
		break;
	case Pivots::CB:
		tr.setOrigin(wc, h);
		break;
	case Pivots::RB:
		tr.setOrigin(w, h);
		break;
	default:
		break;
	}
}

int Utility::Random(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int radios = max - min;
	return min + gen() % radios;
}

float Utility::GetLength(const Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);;
}

Vector2f Utility::Normalize(Vector2f vector)
{
	float length = GetLength(vector);
	if (length != 0.f)
	{
		return vector /= length;
	}
	return vector;
}

float Utility::GetAngle(const Vector2f& from, const Vector2f& to)
{
	Vector2f dir = to - from;
	float radian = atan2(dir.y, dir.x);
	float degree = radian * 180.f / 3.141592f;
	return degree;
}

Pivots Utility::CollisionDir(FloatRect start, FloatRect comp)
{
	float startLeft = start.left;
	float startWidth = start.left + start.width;
	float startTop = start.top;
	float startHeight = start.top + start.height;

	float compLeft = comp.left;
	float compWidth = comp.left + comp.width;
	float compTop = comp.top;
	float compHeight = comp.top + comp.height;

	// start = 맵, comp = 충돌체
	// 왼쪽
	if (compLeft < startWidth && compWidth > startWidth)
	{
		return Pivots::LC;
	}
	// 오른쪽
	else if (compWidth > startLeft && compLeft < startLeft)
	{
		return Pivots::RC;
	}
	// 위
	else if (compTop < startHeight && compHeight > startHeight)
	{
		return Pivots::CT;
	}
	// 아래
	else if(compHeight > startTop && compTop < startTop)
	{
		return Pivots::CB;
	}
	//// 좌하단
	//else if ((compLeft < startWidth && compWidth > startWidth) &&
	//	(compHeight > startTop && compTop < startTop))
	//{
	//	return Pivots::LB;
	//}
	//// 좌상단
	//else if ((compLeft < startWidth && compWidth > startWidth) &&
	//	(compTop < startHeight && compHeight > startHeight))
	//{
	//	return Pivots::LT;
	//}
	//// 우하단
	//else if ((compWidth > startLeft && compLeft < startLeft) &&
	//	(compHeight > startTop && compTop < startTop))
	//{
	//	return Pivots::RB;
	//}
	//// 우상단
	//else /*if ((compWidth > startLeft && compLeft < startLeft) &&
	//	(compTop < startHeight && compHeight > startHeight))*/
	//{
	//	return Pivots::RT;
	//}

	return Pivots();
}
