#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "GameObject.h"
#include "TileSet.h"
#include <istream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

class TileMap : public Component
{
private:
  vector<int> tileMatrix;
  TileSet *tileSet;
  int mapWidth;
  int mapHeight;
  int mapDepth;
  float parallax;

public:
  TileMap(GameObject &associated, string file, TileSet *tileSet, float parallax);

  void Load(string file);
  void SetTileSet(TileSet *tileSet);
  int &At(int x, int y, int z);
  void RenderLayer(int layer, int cameraX, int cameraY);
  int GetWidth();
  int GetHeight();
  int GetDepth();

  void Update(float dt);
  void Render();
  bool Is(string type);
};

#endif