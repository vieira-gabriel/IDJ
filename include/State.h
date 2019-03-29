#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Sprite.h"
#include "Music.h"
#include <SDL_include.h>

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
  void Update(float dt);
  void Render();
};

#endif STATE_H