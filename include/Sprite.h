#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include <iostream>

using namespace std;

class Sprite
{
  private:
    SDL_Texture *texture;
    int width;
    int hight;
    SDL_Rect clipRect;

  public:
    Sprite();
    Sprite(string);
    ~Sprite();
    void Open(string);
    void SetClip(int, int, int, int);
    void Render(int, int);
    int GetWidth();
    int GetHight();
    bool IsOpen();
};

#endif SPRITE_H