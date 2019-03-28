#ifndef GAME_H_INCLUDE
#define GAME_H_INCLUDE

#include <SDL.h>
#include <SDL_include.h>
#include <SDL_mixer.h>
#include <State.h>
#include <iostream>

using namespace std;

class Game
{
private:
  Game(string title, int width, int height);
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