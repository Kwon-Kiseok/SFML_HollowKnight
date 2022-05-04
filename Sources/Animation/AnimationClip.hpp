#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
// ������ �����ӿ� ���������� ���ͷ� ����־���Ѵ�.

enum class AnimationLoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	Texture texture;
	IntRect texCoord;
	//�������� �ش��ϴ� ���� �־��� Vector2f origin;
	Vector2f origin;

	AnimationFrame(const Texture& tex, const IntRect& coord, const Vector2f& ori);
};

struct AnimationClip
{
	std::string id;	// ���� �ִϸ��̼��� �������??
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType;// �ִϸ��̼��� �������� ���� ������� => �ִϸ��̼� Ŭ������ �ٸ��� �ִ�
	int fps;// �������� � �������� �ٲ���( ���� 1�ʴ� ���������� �����Ŵ� ) => �ִϸ��̼� Ŭ������ �ٸ��� �ִ�
};

