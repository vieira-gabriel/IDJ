#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Vec2.h"
#include "Rect.h"
#include "Face.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <SDL_include.h>
#include <string>
#include <vector>
#include <memory>
#include <utility>

class State
{
private:
  shared_ptr<GameObject> bg;
  Music music;
  bool quitRequested;

  void Input();
  void AddObject(int mouseX, int mouseY);
  std::vector<std::shared_ptr<GameObject>> objectArray;

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};

#endif