#include "Bench.hpp"
#include "../Collider.hpp"
#include "../../Managers/PlayerDataManager.hpp"

#include <iostream>

Bench::Bench()
	:Stable()
{
	SetTag(TAG::BENCH);
	collidable = true;
	interactable = false;
	type = Interaction_Type::BENCH;
	SetName("bench");

	SetTexture("Resources/Sprite/BG/Town/town_bench.png");
	SetSprite();
	SetOriginCenter();

	collider = new Collider(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height), GetPosition());
	
}

Bench::~Bench()
{
}

void Bench::Interaction(Player& player)
{
	if (interactable)
	{
		std::cout << "Hero use Bench" << std::endl;
		// �÷��̾� ���ÿ����� ȸ�� �� �ִϸ��̼� ���(���¸� ��ġ�� �ٲ�)
		for (int i = player.GetHealth(); i < MAX_HEALTH; ++i)
		{
			player.SetHealth(1);
		}

		// ���� ����
		PlayerDataManager::GetInstance().SavePlayerData(player);
		PlayerDataManager::GetInstance().SaveBenchPoint(GetPosition());
		interactable = false;
	}
}

void Bench::Render(RenderWindow& window)
{
	window.draw(sprite);
}

bool Bench::Collision(GameObject* otherObj)
{
	return false;
}
