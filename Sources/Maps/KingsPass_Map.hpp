#pragma once
#include "Map.hpp"

// �÷��̾� ���̾� 5�� �������� ����

using namespace sf;

class Portal;
class KingsPass_Map : public Map
{
private:
	Portal* kpToCR;
public:
	KingsPass_Map(Player* player_);
	virtual ~KingsPass_Map() {}
};

