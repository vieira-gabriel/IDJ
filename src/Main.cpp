#include <iostream>
#include "Game.h"
#include "TitleState.h"

using namespace std;

int main(int argc, char **argv)
{
    Game &game = Game::GetInstance();
    TitleState *stg = new TitleState();

    std::cout << "Game created" << std::endl
              << "Starting game" << std::endl;
    game.Push(stg);
    game.Run();

    cout << "Closing game" << endl;

    return 0;
}
