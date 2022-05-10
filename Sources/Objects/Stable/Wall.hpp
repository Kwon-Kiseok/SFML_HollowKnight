#pragma once
#include "Stable.hpp"

class Wall : public Stable
{
public:
	Wall();
	Wall(int idx);
	virtual ~Wall();
};

