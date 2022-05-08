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

int BackgroundImages::GetIndexTotal()
{
	return index_total;
}

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

	SetName(index);
	SetTexture(path + index);
	SetSprite();
}

TownLayered::~TownLayered()
{

}