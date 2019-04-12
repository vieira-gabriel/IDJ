#ifndef TILE_SET_H
#define TILE_SET_H

#include <Sprite.h>

using namespace std;

class TileSet
{
private:
  Sprite tileSet;
  int row;
  int columns;
  int tileWidth;
  int tileHeight;

public:
  TileSet(int tileWidth, int tileHeight, string file);
  ~TileSet();

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();
};

#endif