#include <Sprite.h>
#include <Game.h>
#include "Resources.h"

#define X_DEFAULT 0
#define Y_DEFAULT 0

Uint32 *format = nullptr;
int *access = nullptr;

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
}
Sprite::Sprite(GameObject &associated, string file) : Component(associated)
{
    texture = nullptr;
    Sprite::Open(file);
}

Sprite::~Sprite()
{
    // Resource treats the texture destruction SDL_DestroyTexture(texture);
}

void Sprite::Open(string file)
{
    Game &game = Game::GetInstance();

    // if (Sprite::IsOpen())
    //     Resource treats the texture destruction SDL_DestroyTexture(texture);

    cout << "File: " << file << endl;

    texture = Resources::GetImage(file.c_str()); //IMG_LoadTexture(game.GetRenderer(), file.c_str());
    if (texture == nullptr)
    {
        std::cout << "Fail to load texture " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_QueryTexture(texture, format, access, &width, &height);
    SetClip(X_DEFAULT, Y_DEFAULT, GetWidth(), GetHeight());
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render()
{
    Game &instance = Game::GetInstance();
    SDL_Rect dstRect;
    dstRect.x = associated.box.x;
    dstRect.y = associated.box.y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if (SDL_RenderCopy(instance.GetRenderer(), texture, &clipRect, &dstRect) != 0)
    {
        std::cout << "Fail to render the texture: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Sprite::Render(int x, int y)
{
    Game &instance = Game::GetInstance();
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if (SDL_RenderCopy(instance.GetRenderer(), texture, &clipRect, &dstRect) != 0)
    {
        std::cout << "Fail to render the texture: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

int Sprite::GetHeight()
{
    return height;
}

int Sprite::GetWidth()
{
    return width;
}

bool Sprite::IsOpen()
{
    bool ret = (texture != nullptr) ? true : false;
    return ret;
}

void Sprite::Update(float dt)
{
}

bool Sprite::Is(string type)
{
    // Return true if the type wanted is Sprite
    bool ret = (type == "Sprite") ? true : false;
    return ret;
}