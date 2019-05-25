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
  static unordered_map<std::string, shared_ptr<SDL_Texture>> imageTable;
  static unordered_map<std::string, shared_ptr<Mix_Music>> musicTable;
  static unordered_map<std::string, shared_ptr<Mix_Chunk>> soundTable;
  static unordered_map<std::string, shared_ptr<TTF_Font>> fontTable;

public:
  static shared_ptr<SDL_Texture> GetImage(string file);
  static void ClearImages();

  static shared_ptr<Mix_Music> GetMusic(string file);
  static void ClearMusics();

  static shared_ptr<Mix_Chunk> GetSound(string file);
  static void ClearSounds();

  static shared_ptr<TTF_Font> GetFont(string file, int fontSize);
  static void ClearFont();
};