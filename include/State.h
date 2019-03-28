#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

#include "SDL.h"
#include <iostream>

using namespace std;

class State
{
private:
  /* data */
  Sprite bg;
  Music music;
  bool quitRequested;

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float);
  void Render();
};

#endif STATE_H