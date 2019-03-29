#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char **argv)
{
    Game &game = Game::GetInstance();
    std::cout << "Game created" << std::endl
              << "Starting game" << std::endl;
    game.Run();

    return 0;
}
