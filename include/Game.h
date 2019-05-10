#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include "InputManager.h"
#include "State.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

class State;

class Game
{
private:
  Game(string title, int width, int height);
  /* data */
  static Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;
  State *state;
  int frameStart;
  float dt;

  void CalculateDeltaTime();

public:
  ~Game();
  void Run();
  SDL_Renderer *GetRenderer();
  State &GetState();
  static Game &GetInstance();
  float GetDeltaTime();
};