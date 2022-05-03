#include "AnimationClip.hpp"

AnimationFrame::AnimationFrame(const Texture& tex, const IntRect& coord)
	: texture(tex), texCoord(coord)
{
}
