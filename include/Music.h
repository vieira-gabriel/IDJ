#ifndef MUSIC_H
#define MUSIC_H

#include "SDL.h"
#include <iostream>

using namespace std;

class Music
{
  private:
    Mix_Music *music;

  public:
    Music();
    Music(std::string);
    ~Music();
    void Play(int);
    void Stop(int);
    void Open(std::string);
    bool IsOpen();
};

#endif MUSIC_H