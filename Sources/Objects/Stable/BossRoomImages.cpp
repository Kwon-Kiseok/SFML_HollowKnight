#include "BossRoomImages.hpp"

BossRoomImages::BossRoomImages(int idx)
	:BackgroundImages(idx)
{
	index_total = 8;
	std::string path = "Resources/Sprite/BG/BossRoom/background/";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "cd_room_beam_glow.png";
		break;
	case 2:
		index = "cd_room_BG_01.png";
		break;
	case 3:
		index = "cd_room_BG_02.png";
		break;
	case 4:
		index = "guard_clubs.png";
		break;
	case 5:
		index = "guard_table_01.png";
		break;
	case 6:
		index = "guard_table_02.png";
		break;
	case 7:
		index = "guard_table_03.png";
		break;
	case 8:
		index = "guardian_bench.png";
		break;
	}

	SetName("bossRoom");
	SetTexture(path + index);
	SetSprite();
}
