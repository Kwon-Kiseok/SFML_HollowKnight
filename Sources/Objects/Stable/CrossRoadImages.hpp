#pragma once
#include "BackgroundImages.hpp"

class CrossRoadImages : public BackgroundImages
{
public:
	CrossRoadImages() { index_total = 19; };
	CrossRoadImages(int idx);
	virtual ~CrossRoadImages() {};
};

class CrossRoadBG : public BackgroundImages
{
public:
	CrossRoadBG() { index_total = 16; };
	CrossRoadBG(int idx);
	virtual ~CrossRoadBG() {};
};

class CrossRoadRoof : public BackgroundImages
{
public:
	CrossRoadRoof() { index_total = 6; };
	CrossRoadRoof(int idx);
	virtual ~CrossRoadRoof() {};
};

class CrossRoadWall : public BackgroundImages
{
public:
	CrossRoadWall() { index_total = 31; };
	CrossRoadWall(int idx);
	virtual ~CrossRoadWall() {};
};

class CrossRoadCentral : public BackgroundImages
{
public:
	CrossRoadCentral() { index_total = 7; };
	CrossRoadCentral(int idx);
	virtual ~CrossRoadCentral() {};
};

class CrossRoadElev : public BackgroundImages
{
public:
	CrossRoadElev() { index_total = 24; };
	CrossRoadElev(int idx);
	virtual ~CrossRoadElev() {};
};

class CrossRoadObjects : public BackgroundImages
{
public:
	CrossRoadObjects() { index_total = 7; };
	CrossRoadObjects(int idx);
	virtual ~CrossRoadObjects() {};
};