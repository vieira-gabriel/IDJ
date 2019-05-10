#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include <iostream>
#include <Component.h>
#include "Camera.h"

using namespace std;

class Sprite : public Component
{
private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, string file);
  ~Sprite();
  void Open(string file);
  void SetClip(int x, int y, int w, int h);
  void Render();
  void Render(int x, int y);
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  void Update(float dt);
  bool Is(string type);
};