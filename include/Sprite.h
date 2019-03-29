#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include <iostream>
#include <Component.h>

using namespace std;

class Sprite : public Component
{
private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:
  Sprite() : Component(GameObject &associated));
  Sprite(string file) : Component(GameObject &associated));
  ~Sprite();
  void Open(string file);
  void SetClip(int x, int y, int w, int h);
  void Render();
  int GetWidth();
  int GetHeight();
  bool IsOpen();
};

#endif