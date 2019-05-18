#include "TileMap.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet, float parallax = 0) : Component(associated), parallax(parallax)
{
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(string file)
{
    ifstream tMap;
    string entrada;
    if (tMap.fail())
        cout << "Fail to open Tile Map file" << endl;
    else
    {
        tMap.open(file, ifstream::in);

        getline(tMap, entrada, ',');
        mapWidth = stoi(entrada);

        getline(tMap, entrada, ',');
        mapHeight = stoi(entrada);

        getline(tMap, entrada, ',');
        mapDepth = stoi(entrada);

        stringstream ss;

        int i;

        while (tMap.good())
        {
            getline(tMap, entrada);

            ss << entrada;

            // if (!entrada.empty())
            //     cout << entrada << endl;

            while (ss >> i)
            {
                tileMatrix.push_back(i - 1);

                if (ss.peek() == ',' || ss.peek() == '\n' || ss.peek() == '\0')
                    ss.ignore();
            }
            ss.clear();
        }
        // for (int j = 0; j < tileMatrix.size(); j++)
        // {
        //     std::cout << tileMatrix.at(j) << " ";
        //     if (j % 25 == 24)
        //         cout << endl;
        // }

        tMap.close();
    }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z = 0)
{
    int tile = (mapHeight * mapWidth * z) + (y * mapWidth) + x;

    return tileMatrix[tile];
}

void TileMap::Render()
{
    for (int i = 0; i < mapDepth; i++)
        RenderLayer(i, Camera::pos.x * (1 + parallax * i), Camera::pos.y * (1 + parallax * i));
}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0)
{
    for (int j = 0; j < mapHeight; j++)
    {
        for (int i = 0; i < mapWidth; i++)
        {
            int posX = i * tileSet->GetTileWidth() - cameraX;
            int posY = j * tileSet->GetTileHeight() - cameraY;

            tileSet->RenderTile(At(i, j, layer), posX, posY);
        }
    }
}

int TileMap::GetWidth()
{
    return mapWidth;
}

int TileMap::GetHeight()
{
    return mapHeight;
}

int TileMap::GetDepth()
{
    return mapDepth;
}

void TileMap::Update(float dt)
{
}
bool TileMap::Is(string type)
{
    // Return true if the type wanted is TileMap
    return (type == "TileMap");
}