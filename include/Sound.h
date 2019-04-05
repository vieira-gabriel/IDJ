#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include <iostream>
#include <string>

using namespace std;

class Sound : public Component
{
private:
  Mix_Chunk *chunk;
  int channel;

public:
  Sound(GameObject &associated);
  Sound(GameObject &associated, string file);
  ~Sound();

  void Play(int times);
  void Stop();
  void Open(string file);
  bool IsOpen();
  void Update(float dt);
  void Render();
  bool Is(string file);
};

#endif