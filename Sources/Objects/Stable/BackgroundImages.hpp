#pragma once
#include "Stable.hpp"

class BackgroundImages : public Stable
{
protected:
	int imageIdx;
	int index_total;

public:
	BackgroundImages() {}
	BackgroundImages(int idx);
	virtual ~BackgroundImages();
	int GetIndexTotal();
};

class TownLayered : public BackgroundImages
{
public:
	TownLayered();
	TownLayered(int idx);
	virtual ~TownLayered();
};