#pragma once
#include "Stable.hpp"

class BackgroundImages : public Stable
{
protected:
	int imageIdx;
public:
	BackgroundImages(int idx);
	virtual ~BackgroundImages();
};

class TownLayered : public BackgroundImages
{
public:
	TownLayered(int idx);
	virtual ~TownLayered();
};