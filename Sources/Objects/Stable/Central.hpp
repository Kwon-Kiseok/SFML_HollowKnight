#pragma once
#include "BackgroundImages.hpp"

class Central : public BackgroundImages
{
public:
	Central() { index_total = 7; }
	Central(int idx);
	virtual ~Central() {}
};

