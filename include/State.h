#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Vec2.h"
#include "Rect.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include <SDL_include.h>
#include <string>
#include <vector>
#include <memory>

const string BACKGROUND_SPRITE = "assets/img/ocean.jpg";
#define BACKGROUND_MUSIC "assets/audio/stageState.ogg"
#define PENGUIN_SOURCE "assets/img/penguinface.png"
#define PENGUIN_SOUND "assets/audio/boom.wav"
#define TILE_MAP_SOURCE "assets/map/tileMap.txt"
#define TILE_SET_SOURCE "assets/img/tileset.png"
#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define MINIONS 4
#define PARALAX 2

class State
{
public:
  State();
  virtual ~State();

  virtual void LoadAssets() = 0;
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;

  virtual void Start() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

  virtual weak_ptr<GameObject> AddObject(GameObject *go);
  virtual weak_ptr<GameObject> GetObjectPtr(GameObject *go);

  bool QuitRequested();
  bool PopRequested();

protected:
  bool popRequested;
  bool quitRequested;
  bool started;

  vector<shared_ptr<GameObject>> objectArray;

  void StartArray();
  virtual void UpdateArray(float dt);
  virtual void RenderArray();
};