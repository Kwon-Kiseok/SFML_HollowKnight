#pragma once
#include "BackgroundImages.hpp"

class BossRoomImages : public BackgroundImages
{
public:
	BossRoomImages() { index_total = 8; }
	BossRoomImages(int idx);
	virtual ~BossRoomImages() {}
};

