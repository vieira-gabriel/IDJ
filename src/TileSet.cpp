#include "TileSet.h"

GameObject *GO = new GameObject;

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileSet(*GO, file)
{
    if (tileSet.IsOpen())
    {
        this->tileHeight = tileHeight;
        this->tileWidth = tileWidth;
        row = tileSet.GetHeight() / this->tileHeight;
        columns = tileSet.GetWidth() / this->tileWidth;
    }
    else
    {
        cout << "Fail to load tileset: " << endl;
        exit(1);
    }
}

TileSet::~TileSet()
{
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
    unsigned int tiles = row * columns;
    if (index < tiles)
    {
        tileSet.SetClip(tileWidth * (index % columns), tileHeight * (index / columns), tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;
}
