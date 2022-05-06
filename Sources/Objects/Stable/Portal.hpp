#pragma once
#include "Stable.hpp"
#include "../../Managers/MapManager.hpp"

class Portal : public Stable
{
private:
	MAP_TYPE currMap;
	MAP_TYPE nextMap;
public:
	Portal();
	virtual ~Portal();

	MAP_TYPE& GetCurrentMap();
	void SetNextMap(MAP_TYPE next);
	virtual void Interaction() override;
	virtual void Render(RenderWindow& window) override;
	virtual bool Collision(GameObject* otherObj) override;
};

