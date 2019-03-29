#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include <iostream>

using namespace std;

class Music
{
private:
  Mix_Music *music;

public:
  Music();
  Music(string file);
  ~Music();
  void Play(int times);
  void Stop(int msToStop);
  void Open(string file);
  bool IsOpen();
};

#endif