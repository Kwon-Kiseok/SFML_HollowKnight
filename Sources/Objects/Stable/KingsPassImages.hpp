#pragma once
#include "BackgroundImages.hpp"

class KingsPassImages : public BackgroundImages
{
public:
	KingsPassImages();
	KingsPassImages(int idx);
	virtual ~KingsPassImages();
};

class KingsPassBG : public BackgroundImages
{
public:
	KingsPassBG();
	KingsPassBG(int idx);
	virtual ~KingsPassBG();
};

class KingsPassWall : public BackgroundImages
{
public:
	KingsPassWall();
	KingsPassWall(int idx);
	virtual ~KingsPassWall();
};

class KingsPassObjects : public BackgroundImages
{
public:
	KingsPassObjects();
	KingsPassObjects(int idx);
	virtual ~KingsPassObjects();
};