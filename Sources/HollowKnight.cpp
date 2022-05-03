#include "Framework/Game.hpp"

int main()
{
    Game::GetInstance().Init();
    Game::GetInstance().Update();
    Game::GetInstance().Release();
    return 0;
}