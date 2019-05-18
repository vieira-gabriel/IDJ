#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include <iostream>
#include <Component.h>
#include "Camera.h"
#include "Timer.h"

using namespace std;

class Sprite : public Component
{
private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;
  Vec2 scale;
  int frameCount;
  int currentFrame;
  float timeElapsed;
  float frameTime;

  float secondsToSelfDestruct;
  Timer selfDestructCount;

public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0.0);
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
  void SetScaleX(float scaleX, float scaleY);
  Vec2 GetScale();
  void SetFrame(int frame);
  void SetFrameCount(int frameCount);
  void SetFrameTime(float frameTime);
};