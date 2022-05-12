#pragma once
#include "Stable.hpp"
#include "../../Managers/MapManager.hpp"

class Portal : public Stable
{
private:
	MAP_TYPE currMap;
	MAP_TYPE nextMap;
	Vector2f spawnPos;

public:
	Portal();
	virtual ~Portal();

	MAP_TYPE& GetCurrentMap();
	MAP_TYPE& GetNextMap();
	void SetCurrMap(MAP_TYPE curr);
	void SetNextMap(MAP_TYPE next, Vector2f pos);
	virtual void Interaction(Player& player) override;
	virtual void Render(RenderWindow& window) override;
	virtual bool Collision(GameObject* otherObj) override;
};

