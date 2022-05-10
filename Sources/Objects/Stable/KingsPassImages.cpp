#include "KingsPassImages.hpp"

/// <summary>
/// 
/// </summary>
KingsPassImages::KingsPassImages()
{
	index_total = 19;
}

KingsPassImages::KingsPassImages(int idx)
	: BackgroundImages(idx)
{
	index_total = 19;

	std::string path = "Resources/Sprite/BG/Tutorial/tut_edge_0";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "1_0000_05.png";
		break;
	case 2:
		index = "1_0001_04.png";
		break;
	case 3:
		index = "1_0002_03.png";
		break;
	case 4:
		index = "1_0003_02.png";
		break;
	case 5:
		index = "1_0004_01.png";
		break;
	case 6:
		index = "2_0000_04.png";
		break;
	case 7:
		index = "2_0001_03.png";
		break;
	case 8:
		index = "2_0002_02.png";
		break;
	case 9:
		index = "2_0003_01.png";
		break;
	case 10:
		path = "Resources/Sprite/BG/Tutorial/Tut_msk_0";
		index = "1.png";
		break;
	case 11:
		path = "Resources/Sprite/BG/Tutorial/Tut_msk_0";
		index = "3.png";
		break;
	case 12:
		path = "Resources/Sprite/BG/Tutorial/Tut_msk_0";
		index = "4.png";
		break;
	case 13:
		path = "Resources/Sprite/BG/Tutorial/Tut_msk_0";
		index = "5.png";
		break;
	case 14:
		path = "Resources/Sprite/BG/Tutorial/Tut_msk_0";
		index = "6.png";
		break;
	case 15:
		path = "Resources/Sprite/BG/Tutorial/tut_rocks_000";
		index = "3_06.png";
		break;
	case 16:
		path = "Resources/Sprite/BG/Tutorial/tut_rocks_000";
		index = "4_05.png";
		break;
	case 17:
		path = "Resources/Sprite/BG/Tutorial/tut_rocks_000";
		index = "6_03.png";
		break;
	case 18:
		path = "Resources/Sprite/BG/Tutorial/tut_rocks_000";
		index = "7_02.png";
		break;
	case 19:
		path = "Resources/Sprite/BG/Tutorial/tut_rocks_000";
		index = "8_01.png";
		break;
	}

	SetName("kpImages");
	SetTexture(path + index);
	SetSprite();
}

KingsPassImages::~KingsPassImages()
{
}

/// <summary>
/// 
/// </summary>
KingsPassBG::KingsPassBG()
{
	index_total = 12;
}

KingsPassBG::KingsPassBG(int idx)
	: BackgroundImages(idx)
{
	index_total = 12;

	std::string path = "Resources/Sprite/BG/Tutorial/tut_BG_set_0";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "1_0000_05.png";
		break;
	case 2:
		index = "1_0001_04.png";
		break;
	case 3:
		index = "1_0002_03.png";
		break;
	case 4:
		index = "1_0003_02.png";
		break;
	case 5:
		index = "1_0004_01.png";
		break;
	case 6:
		index = "2_0000_06.png";
		break;
	case 7:
		index = "2_0001_05.png";
		break;
	case 8:
		index = "2_0002_04.png";
		break;
	case 9:
		index = "2_0003_03.png";
		break;
	case 10:
		index = "2_0004_02.png";
		break;
	case 11:
		index = "2_0005_01.png";
		break;
	case 12:
		path = "Resources/Sprite/BG/Tutorial/tut_door_large_0006_05.png";
		index = "";
		break;
	}

	SetName("kpBG");
	SetTexture(path + index);
	SetSprite();
}

KingsPassBG::~KingsPassBG()
{
}

/// <summary>
/// 
/// </summary>
KingsPassWall::KingsPassWall()
{
	index_total = 17;
}

KingsPassWall::KingsPassWall(int idx)
	: BackgroundImages(idx)
{
	index_total = 17;

	std::string path = "Resources/Sprite/BG/Tutorial/tut_wall_";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "l_0000_09.png";
		break;
	case 2:
		index = "l_0000_10.png";
		break;
	case 3:
		index = "l_0000_11.png";
		break;
	case 4:
		index = "l_0000_12.png";
		break;
	case 5:
		index = "l_0000_13.png";
		break;
	case 6:
		index = "l_0000_14.png";
		break;
	case 7:
		index = "l_0001_08.png";
		break;
	case 8:
		index = "l_0002_07.png";
		break;
	case 9:
		index = "l_0003_06.png";
		break;
	case 10:
		index = "l_0007_02.png";
		break;
	case 11:
		index = "l_0008_01.png";
		break;
	case 12:
		index = "r_0000_06.png";
		break;
	case 13:
		index = "r_0001_05.png";
		break;
	case 14:
		index = "r_0002_04.png";
		break;
	case 15:
		index = "r_0003_03.png";
		break;
	case 16:
		index = "r_0004_02.png";
		break;
	case 17:
		index = "r_0005_01.png";
		break;
	}

	SetName("kpWall");
	SetTexture(path + index);
	SetSprite();
}

KingsPassWall::~KingsPassWall()
{
}

/// <summary>
/// 
/// </summary>
KingsPassObjects::KingsPassObjects()
{
	index_total = 5;
}

KingsPassObjects::KingsPassObjects(int idx)
	: BackgroundImages(idx)
{
	index_total = 5;

	std::string path = "Resources/Sprite/BG/Tutorial/";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "tut_tab_ancient_0000_3.png";
		break;
	case 2:
		index = "tut_tab_ancient_0001_2.png";
		break;
	case 3:
		index = "tut_tab_ancient_0002_1.png";
		break;
	case 4:
		index = "tutorial_poles_0003_b1.png";
		break;
	case 5:
		index = "tutorial_poles_0008_a.png";
		break;
	}

	SetName("kpObjects");
	SetTexture(path + index);
	SetSprite();
}

KingsPassObjects::~KingsPassObjects()
{
}
