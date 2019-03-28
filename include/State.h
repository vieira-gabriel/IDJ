#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

#include "SDL.h"

class State
{
private:
  /* data */
  Sprite bg;
  //Music music;
  bool quitRequested;

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};

#endif STATE_H