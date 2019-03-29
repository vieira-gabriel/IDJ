#include <Sprite.h>
#include <Game.h>

#define X_DEFAULT 0
#define Y_DEFAULT 0

Uint32 *format = nullptr;
int *access = nullptr;

Sprite::Sprite() : Component(GameObject &associated))
{
    texture = nullptr;
}
Sprite::Sprite(string file) : Component(GameObject &associated))
{
    texture = nullptr;
    Sprite::Open(file);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

void Sprite::Open(string file)
{
    Game &game = Game::GetInstance();

    if (Sprite::IsOpen())
        SDL_DestroyTexture(texture);
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
    if (texture == nullptr)
    {
        std::cout << "Fail to load texture" << SDL_GetError() << std::endl;
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
    SDL_Rect dstRect = {x, y, clipRect.w, clipRect.h};

    if (SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) != 0)
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

virtual void Sprite::Update(float dt)
{
}

virtual void Sprite::Is(string type)
{
}