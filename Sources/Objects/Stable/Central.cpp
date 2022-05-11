#include "Central.hpp"

Central::Central(int idx)
	:BackgroundImages(idx)
{
	index_total = 7;

	std::string path = "Resources/Sprite/BG/CrossRoad/CentralResource/";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "central light.png";
		break;
	case 2:
		index = "central_BG_unlit.png";
		break;
	case 3:
		index = "central_elev.png";
		break;
	case 4:
		index = "central_elev_base.png";
		break;
	case 5:
		index = "central_elev_cog.png";
		break;
	case 6:
		index = "central_elev_strut.png";
		break;
	case 7:
		index = "central_FG.png";
		break;
	}

	SetName("central");
	SetTexture(path + index);
	SetSprite();
}
