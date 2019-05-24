#include <iostream>
#include "Game.h"
#include "StageState.h"

using namespace std;

int main(int argc, char **argv)
{
    Game &game = Game::GetInstance();
    StageState *stg = new StageState();

    std::cout << "Game created" << std::endl
              << "Starting game" << std::endl;
    game.Push(stg);
    game.Run();

    cout << "Closing game" << endl;

    return 0;
}
