#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <SDL_include.h>
#include "InputManager.h"
#include "State.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <time.h>
#include <stack>

#define CHUNKSIZE 1024
#define WINDOW_FLAG 0
#define AUDIO_CHANNELS 32

using namespace std;

class State;

class Game
{
private:
  static Game *instance;

  State *storedState;
  SDL_Window *window;
  SDL_Renderer *renderer;
  stack<unique_ptr<State>> stateStack;

  int frameStart;
  float dt;

  void CalculateDeltaTime();

public:
  Game(string title, int width, int height);
  ~Game();

  static Game &GetInstance();
  SDL_Renderer *GetRenderer();
  State &GetCurrentState();

  void Push(State *state);
  void Run();

  float GetDeltaTime();
};