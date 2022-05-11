#include "MapperScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/UIManager.hpp"

void MapperScene::Init()
{
	textureHomeBG = TextureManager::GetInstance().GetTexture("Resources/Sprite/Mapper_home_0003_a_02.png");
	spriteHomeBG.setTexture(textureHomeBG);
	spriteHomeBG.setPosition(700, 500);

	textureLight = TextureManager::GetInstance().GetTexture("Resources/Sprite/Mapper_home_0002_a.png");
	spriteLight.setTexture(textureLight);
	spriteLight.setPosition(700, 500);
	textureHome = TextureManager::GetInstance().GetTexture("Resources/Sprite/Mapper_home_0000_a.png");
	spriteHome.setTexture(textureHome);
	spriteHome.setPosition(740, 520);
	textureDesk = TextureManager::GetInstance().GetTexture("Resources/Sprite/Mapper_home_0001_a.png");
	spriteDesk.setTexture(textureDesk);
	spriteDesk.setPosition(1000, 600);

	textureIsadela = TextureManager::GetInstance().GetTexture("Resources/Sprite/NPCIselda.png");
	spriteIsadela.setTexture(textureIsadela);
	spriteIsadela.setPosition(1100, 710);

//	textureIselda_idle = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/Iselda_Idle.png");


}

void MapperScene::Update(float dt)
{
}

void MapperScene::Render(RenderWindow& window)
{
	window.draw(spriteHomeBG);
	window.draw(spriteIsadela);
	window.draw(spriteDesk);
	window.draw(spriteHome);
//	window.draw(spriteIselda_idle);
}

void MapperScene::Release()
{
}
