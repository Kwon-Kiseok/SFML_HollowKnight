#include "CrossRoadImages.hpp"

CrossRoadImages::CrossRoadImages(int idx)
	:BackgroundImages(idx)
{
	index_total = 19;

	std::string path = "Resources/Sprite/BG/CrossRoad/Images";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "cd_archway_01.png";
		break;
	case 2:
		index = "cd_archway_01_broken.png";
		break;
	case 3:
		index = "cd_archway_02.png";
		break;
	case 4:
		index = "cd_archway_03.png";
		break;
	case 5:
		index = "cd_archway_04.png";
		break;
	case 6:
		index = "cd_archway_04_r.png";
		break;
	case 7:
		index = "cd_bridge_collapse_01.png";
		break;
	case 8:
		index = "cd_bridge_collapse_02.png";
		break;
	case 9:
		index = "cd_bridge_collapse_03.png";
		break;
	case 10:
		index = "cd_pillar_01.png";
		break;
	case 11:
		index = "cd_pillar_02.png";
		break;
	case 12:
		index = "cd_pillar_03.png";
		break;
	case 13:
		index = "Hallownest_Gate_0013_07.png";
		break;
	case 14:
		index = "Hallownest_Gate_0014_06.png";
		break;
	case 15:
		index = "Hallownest_Gate_0015_05.png";
		break;
	case 16:
		index = "Hallownest_Gate_0016_04.png";
		break;
	case 17:
		index = "Hallownest_Gate_0017_03.png";
		break;
	case 18:
		index = "Hallownest_Gate_0018_02.png";
		break;
	case 19:
		index = "Hallownest_Gate_0019_01.png";
		break;
	}

	SetName("crImages");
	SetTexture(path + index);
	SetSprite();
}

CrossRoadBG::CrossRoadBG(int idx)
	: BackgroundImages(idx)
{
	index_total = 16;

	std::string path = "Resources/Sprite/BG/CrossRoad/background";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "bg_coccon_01.png";
		break;
	case 2:
		index = "bg_cocoon_02.png";
		break;
	case 3:
		index = "BG_egg_05.png";
		break;
	case 4:
		index = "BG_egg_07_0000_Layer-1.png";
		break;
	case 5:
		index = "BG_egg_07_0001_Layer-2.png";
		break;
	case 6:
		index = "BG_egg_07_0002_Layer-3.png";
		break;
	case 7:
		index = "BG_egg_07_0003_Layer-4.png";
		break;
	case 8:
		index = "BG_egg_07_0004_Layer-6.png";
		break;
	case 9:
		index = "BG_egg_07_0005_Layer-0_0.png";
		break;
	case 10:
		index = "BG_egg_07_0006_Layer-5.png";
		break;
	case 11:
		index = "cd_BG_bone_01.png";
		break;
	case 12:
		index = "cd_BG_bone_02.png";
		break;
	case 13:
		index = "cd_BG_egg_01.png";
		break;
	case 14:
		index = "cd_BG_egg_03.png";
		break;
	case 15:
		index = "cd_BG_egg_04.png";
		break;
	case 16:
		index = "cd_BG_well_shaft.png";
		break;
	}

	SetName("crBG");
	SetTexture(path + index);
	SetSprite();
}

CrossRoadRoof::CrossRoadRoof(int idx)
	: BackgroundImages(idx)
{
	index_total = 6;

	std::string path = "Resources/Sprite/BG/CrossRoad/roof";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "cd_big_roof_0000_07.png";
		break;
	case 2:
		index = "cd_big_roof_0001_06.png";
		break;
	case 3:
		index = "cd_big_roof_0002_05.png";
		break;
	case 4:
		index = "cd_big_roof_0004_03.png";
		break;
	case 5:
		index = "cd_big_roof_0005_02.png";
		break;
	case 6:
		index = "cd_big_roof_0006_01.png";
		break;
	}

	SetName("crRoof");
	SetTexture(path + index);
	SetSprite();
}

CrossRoadWall::CrossRoadWall(int idx)
	: BackgroundImages(idx)
{
	index_total = 19;

	std::string path = "Resources/Sprite/BG/CrossRoad/wall";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "break_wall_ancient_variant.png";
		break;
	case 2:
		index = "break_wall_deepnest.png";
		break;
	case 3:
		index = "broken_piece_01.png";
		break;
	case 4:
		index = "broken_piece_02.png";
		break;
	case 5:
		index = "broken_piece_03.png";
		break;
	case 6:
		index = "cd_bone_wall_0000_06.png";
		break;
	case 7:
		index = "cd_bone_wall_0003_03.png";
		break;
	case 8:
		index = "cd_bone_wall_0004_02.png";
		break;
	case 9:
		index = "cd_bone_wall_0005_01.png";
		break;
	case 10:
		index = "cd_broken_wall.png";
		break;
	case 11:
		index = "cd_highway_break_front_01.png";
		break;
	case 12:
		index = "cd_highway_break_front_01_r.png";
		break;
	case 13:
		index = "cd_highway_break_front_02.png";
		break;
	case 14:
		index = "cd_wall_01.png";
		break;
	case 15:
		index = "cd_wall_01_broken.png";
		break;
	case 16:
		index = "cd_wall_01_r.png";
		break;
	case 17:
		index = "cd_wall_01_solid.png";
		break;
	case 18:
		index = "cd_wall_04.png";
		break;
	case 19:
		index = "cd_well_brick_l.png";
		break;
	case 20:
		index = "cd_well_brick_r.png";
		break;
	case 21:
		index = "cr10_break_wall.png";
		break;
	case 22:
		index = "cr21_break_wall.png";
		break;
	case 23:
		index = "crossroads_false_door_0000_4.png";
		break;
	case 24:
		index = "crossroads_false_door_0001_3.png";
		break;
	case 25:
		index = "crossroads_false_door_0002_2.png";
		break;
	case 26:
		index = "crossroads_false_door_0003_1.png";
		break;
	case 27:
		index = "Hallownest_Gate_0005_15.png";
		break;
	case 28:
		index = "Hallownest_Gate_0007_13.png";
		break;
	case 29:
		index = "Hallownest_Gate_0008_12.png";
		break;
	case 30:
		index = "Hallownest_Gate_0010_10.png";
		break;
	case 31:
		index = "Hallownest_Gate_0011_09.png";
		break;
	}

	SetName("kpWall");
	SetTexture(path + index);
	SetSprite();
}

CrossRoadCentral::CrossRoadCentral(int idx)
	: BackgroundImages(idx)
{
	index_total = 7;

	std::string path = "Resources/Sprite/BG/CrossRoad/CentralResource";
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

	SetName("crCentral");
	SetTexture(path + index);
	SetSprite();
}

CrossRoadElev::CrossRoadElev(int idx)
	: BackgroundImages(idx)
{
	index_total = 24;

	std::string path = "Resources/Sprite/BG/CrossRoad/ElevResource";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "elev_back.png";
		break;
	case 2:
		index = "elev_back_arch.png";
		break;
	case 3:
		index = "elev_base.png";
		break;
	case 4:
		index = "elev_bg_plat.png";
		break;
	case 5:
		index = "elev_bg_plat2.png";
		break;
	case 6:
		index = "elev_chain.png";
		break;
	case 7:
		index = "elev_elev_top.png";
		break;
	case 8:
		index = "elev_house_floor.png";
		break;
	case 9:
		index = "elev_lamp.png";
		break;
	case 10:
		index = "elev_lamp_glow.png";
		break;
	case 11:
		index = "elev_lift.png";
		break;
	case 12:
		index = "elev_mid_back.png";
		break;
	case 13:
		index = "elev_mine_wood_back.png";
		break;
	case 14:
		index = "elev_plat_l.png";
		break;
	case 15:
		index = "elev_plat_r.png";
		break;
	case 16:
		index = "elev_room_balcony.png";
		break;
	case 17:
		index = "Elev_room_house_bg.png";
		break;
	case 18:
		index = "elev_shortcut.png";
		break;
	case 19:
		index = "elev_symbol.png";
		break;
	case 20:
		index = "elev_wall.png";
		break;
	case 21:
		index = "elev_wall_02.png";
		break;
	case 22:
		index = "elev_wall_02_r.png";
		break;
	case 23:
		index = "elev_wall_r.png";
		break;
	case 24:
		index = "elev_window.png";
		break;
	}

	SetName("kpImages");
	SetTexture(path + index);
	SetSprite();
}

CrossRoadObjects::CrossRoadObjects(int idx)
	: BackgroundImages(idx)
{
	index_total = 7;

	std::string path = "Resources/Sprite/BG/CrossRoad/object";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "boss_door.png";
		break;
	case 2:
		index = "boss_door_anim0007.png";
		break;
	case 3:
		index = "boss_door_pieces_0003_boss_door_back_01.png";
		break;
	case 4:
		index = "boss_door_pieces_0004_boss_door_back_02.png";
		break;
	case 5:
		index = "brk_cart_01.png";
		break;
	case 6:
		index = "brk_cart_02.png";
		break;
	case 7:
		index = "brk_cart_03.png";
		break;
	}

	SetName("crObjects");
	SetTexture(path + index);
	SetSprite();
}
