#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
// 각각의 프레임에 대한정보를 벡터로 들고있어야한다.

enum class AnimationLoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	Texture texture;
	IntRect texCoord;
	//오리진에 해당하는 값을 넣어줌 Vector2f origin;
	Vector2f origin;

	AnimationFrame(const Texture& tex, const IntRect& coord, const Vector2f& ori);
};

struct AnimationClip
{
	std::string id;	// 무슨 애니메이션을 재생할지??
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType;// 애니메이션이 루프인지 단일 재생인지 => 애니메이션 클립마다 다를수 있다
	int fps;// 프레임은 어떤 간격으로 바꿀지( 보통 1초당 몇프레임을 찍을거다 ) => 애니메이션 클립마다 다를수 있다
};

