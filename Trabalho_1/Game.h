#ifdef GAME_H_INCLUDE

#include "SDL.h"
#include <iostream>

using namespace std;

class Game
{
private:
    Game(string, int, int);
    /* data */
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};

Game::Game(string title, int width, int height)
{
}

Game::~Game()
{
}

Game::GetInstance()
{
    if (instance != nullptr)
    {
    }
    else instance = new;

    return *instance;
}

#endif