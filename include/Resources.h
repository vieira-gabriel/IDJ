#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include "Game.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Resources
{
private:
  static unordered_map<std::string, SDL_Texture *> imageTable;
  static unordered_map<std::string, Mix_Music *> musicTable;
  static unordered_map<std::string, Mix_Chunk *> soundTable;

public:
  static SDL_Texture *GetImage(string file);
  static void ClearImages();

  static Mix_Music *GetMusic(string file);
  static void ClearMusics();

  static Mix_Chunk *GetSound(string file);
  static void ClearSounds();
};