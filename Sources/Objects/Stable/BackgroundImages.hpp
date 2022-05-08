#pragma once
#include "Stable.hpp"

class BackgroundImages : public Stable
{
public:
	BackgroundImages() {}
	BackgroundImages(int idx);
	virtual ~BackgroundImages();
};

class TownLayered : public BackgroundImages
{
public:
	TownLayered();
	TownLayered(int idx);
	virtual ~TownLayered();
};

class TownBuilding : public BackgroundImages
{
public:
	TownBuilding();
	TownBuilding(int idx);
	virtual ~TownBuilding();
};

class TownBG : public BackgroundImages
{
public:
	TownBG();
	TownBG(int idx);
	virtual ~TownBG();
};

class TownGraveCross : public BackgroundImages
{
public:
	TownGraveCross();
	TownGraveCross(int idx);
	virtual ~TownGraveCross();
};

class TownExtra : public BackgroundImages
{
public:
	TownExtra();
	TownExtra(int idx);
	virtual ~TownExtra();
};