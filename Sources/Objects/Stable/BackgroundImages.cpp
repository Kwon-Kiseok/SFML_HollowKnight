#include "BackgroundImages.hpp"

BackgroundImages::BackgroundImages(int idx)
	: Stable()
{
	SetTag(TAG::BACKGROUND);
	collidable = false;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;
}

BackgroundImages::~BackgroundImages()
{
}

/// <summary>
/// 타운 레이어드
/// </summary>
TownLayered::TownLayered()
{
	index_total = 35;
}

TownLayered::TownLayered(int idx)
	: BackgroundImages(idx)
{
	index_total = 35;

	std::string path = "Resources/Sprite/BG/Town/town_layered_00";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "00_37.png";
		break;
	case 2:
		index = "01_36.png";
		break;
	case 3:
		index = "02_35.png";
		break;
	case 4:
		index = "03_34.png";
		break;
	case 5:
		index = "04_33.png";
		break;
	case 6:
		index = "05_32.png";
		break;
	case 7:
		index = "06_31.png";
		break;
	case 8:
		index = "07_30.png";
		break;
	case 9:
		index = "08_29.png";
		break;
	case 10:
		index = "09_28.png";
		break;
	case 11:
		index = "10_27.png";
		break;
	case 12:
		index = "11_26.png";
		break;
	case 13:
		index = "12_25.png";
		break;
	case 14:
		index = "13_24.png";
		break;
	case 15:
		index = "14_23.png";
		break;
	case 16:
		index = "15_22.png";
		break;
	case 17:
		index = "16_21.png";
		break;
	case 18:
		index = "17_20.png";
		break;
	case 19:
		index = "18_19.png";
		break;
	case 20:
		index = "20_17.png";
		break;
	case 21:
		index = "21_16.png";
		break;
	case 22:
		index = "22_152.png";
		break;
	case 23:
		index = "23_14.png";
		break;
	case 24:
		index = "24_13.png";
		break;
	case 25:
		index = "25_12.png";
		break;
	case 26:
		index = "27_10.png";
		break;
	case 27:
		index = "28_09.png";
		break;
	case 28:
		index = "29_08.png";
		break;
	case 29:
		index = "30_07.png";
		break;
	case 30:
		index = "31_06.png";
		break;
	case 31:
		index = "32_05.png";
		break;
	case 32:
		index = "33_04.png";
		break;
	case 33:
		index = "34_03.png";
		break;
	case 34:
		index = "35_02.png";
		break;
	case 35:
		index = "36_01.png";
		break;
	}

	SetName("layered");
	SetTexture(path + index);
	SetSprite();
}

TownLayered::~TownLayered()
{

}

/// <summary>
/// 타운 빌딩
/// </summary>
TownBuilding::TownBuilding()
{
	index_total = 4;
}

TownBuilding::TownBuilding(int idx)
	:BackgroundImages(idx)
{
	index_total = 4;

	std::string path = "Resources/Sprite/BG/Town/town_buildings_left_000";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "0_a.png";
		break;
	case 2:
		index = "1_a.png";
		break;
	case 3:
		index = "2_a.png";
		break;
	case 4:
		index = "3_a.png";
		break;
	}

	SetName("building");
	SetTexture(path + index);
	SetSprite();
}

TownBuilding::~TownBuilding()
{
}

/// <summary>
/// 타운 BG
/// </summary>
TownBG::TownBG()
{
	index_total = 5;
}

TownBG::TownBG(int idx)
	: BackgroundImages(idx)
{
	index_total = 5;
	std::string path = "Resources/Sprite/BG/Town/Town_BG_000";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "0_05_02.png";
		break;
	case 2:
		index = "2_04.png";
		break;
	case 3:
		index = "3_03b.png";
		break;
	case 4:
		index = "5_02b.png";
		break;
	case 5:
		index = "7_01.png";
		break;
	}

	SetName("bg");
	SetTexture(path + index);
	SetSprite();
}

TownBG::~TownBG()
{
}

/// <summary>
/// 타운 그레이브 크로스
/// </summary>
TownGraveCross::TownGraveCross()
{
	index_total = 36;
}

TownGraveCross::TownGraveCross(int idx)
	:BackgroundImages(idx)
{
	index_total = 36;

	std::string path = "Resources/Sprite/BG/Town/town_grave_cross_bits_01_00";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "00.png";
		break;
	case 2:
		index = "01.png";
		break;
	case 3:
		index = "02.png";
		break;
	case 4:
		index = "03.png";
		break;
	case 5:
		index = "04.png";
		break;
	case 6:
		index = "05.png";
		break;
	case 7:
		index = "06.png";
		break;
	case 8:
		index = "07.png";
		break;
	case 9:
		index = "08.png";
		break;
	case 10:
		index = "09.png";
		break;
	case 11:
		index = "10.png";
		break;
	case 12:
		index = "11.png";
		break;
	case 13:
		index = "12.png";
		break;
	case 14:
		index = "13.png";
		break;
	case 15:
		index = "14.png";
		break;
	case 16:
		index = "15.png";
		break;
	case 17:
		index = "16.png";
		break;
	case 18:
		index = "17.png";
		break;
	case 19:
		index = "18.png";
		break;
	case 20:
		index = "19.png";
		break;
	case 21:
		index = "20.png";
		break;
	case 22:
		index = "21.png";
		break;
	case 23:
		index = "22.png";
		break;
	case 24:
		index = "23.png";
		break;
	case 25:
		index = "24.png";
		break;
	case 26:
		index = "25.png";
		break;
	case 27:
		index = "26.png";
		break;
	case 28:
		index = "27.png";
		break;
	case 29:
		index = "28.png";
		break;
	case 30:
		index = "29.png";
		break;
	case 31:
		index = "30.png";
		break;
	case 32:
		index = "31.png";
		break;
	case 33:
		index = "32.png";
		break;
	case 34:
		index = "33.png";
		break;
	case 35:
		index = "34.png";
		break;
	case 36:
		index = "35.png";
		break;
	}

	SetName("graveCross");
	SetTexture(path + index);
	SetSprite();
}

TownGraveCross::~TownGraveCross()
{
}

TownExtra::TownExtra()
{
	index_total = 10;
}

TownExtra::TownExtra(int idx)
	:BackgroundImages(idx)
{
	index_total = 10;

	std::string path = "Resources/Sprite/BG/Town/";
	std::string ex;
	switch (imageIdx)
	{
	case 1:
		ex = "town_extra_rock.png";
		break;
	case 2:
		ex = "town_fence.png";
		break;
	case 3:
		ex = "town_MID_left_02.png";
		break;
	case 4:
		ex = "town_mine_elev_cage000.png";
		break;
	case 5:
		ex = "town_step_01.png";
		break;
	case 6:
		ex = "town_step_02.png";
		break;
	case 7:
		ex = "town_step_02_r.png";
		break;
	case 8:
		ex = "town_well_back.png";
		break;
	case 9:
		ex = "town_well_front.png";
		break;
	case 10:
		ex = "town_well_top.png";
		break;
	}

	SetName("extra");
	SetTexture(path + ex);
	SetSprite();
}

TownExtra::~TownExtra()
{
}
