#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char **argv)
{
    Game &game = Game::GetInstance();
    game.Run();

    return 0;
}
