#include "AnimationClip.hpp"

AnimationFrame::AnimationFrame(const Texture& tex, const IntRect& coord, const Vector2f& ori)
	: texture(tex), texCoord(coord), origin(ori)
{
}

AnimationFrame::AnimationFrame(const Texture& tex)
	: texture(tex)
{
}
