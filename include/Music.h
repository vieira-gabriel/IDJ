#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include <iostream>
#include <memory>

using namespace std;

class Music
{
private:
  shared_ptr<Mix_Music> music;

public:
  Music();
  Music(string file);
  ~Music();
  void Play(int times);
  void Stop(int msToStop);
  void Open(string file);
  bool IsOpen();
};