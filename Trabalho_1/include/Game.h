#ifndef GAME_H_INCLUDE
#define GAME_H_INCLUDE

#include "SDL.h"
#include <iostream>

using namespace std;

class Game
{
private:
  Game(string, int, int);
  /* data */
  static Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;
  State *state;

public:
  ~Game();
  void Run();
  SDL_Renderer *GetRenderer();
  State &GetState();
  static Game &GetInstance();
};

#endif