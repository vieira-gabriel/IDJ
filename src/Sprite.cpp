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
    scale = Vec2(1, 1);
    frameCount = 1;
    frameTime = 1;
    currentFrame = 0;
    timeElapsed = 0;
}
Sprite::Sprite(GameObject &associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated)
{
    texture = nullptr;
    scale = Vec2(1, 1);
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = secondsToSelfDestruct;

    Sprite::Open(file);
    currentFrame = 0;
    timeElapsed = 0;
}

Sprite::~Sprite()
{
    // Resource treats the texture destruction SDL_DestroyTexture(texture);
}

void Sprite::Open(string file)
{
    SDL_DestroyTexture(texture.get());

    texture = Resources::GetImage(file.c_str());
    if (texture == nullptr)
    {
        std::cout << "Fail to load texture " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_QueryTexture(texture.get(), format, access, &width, &height);
    SetClip(X_DEFAULT, Y_DEFAULT, GetWidth(), GetHeight());

    associated.box.w = width;
    associated.box.h = height;
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
    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y)
{
    Game &instance = Game::GetInstance();
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w * scale.x;
    dstRect.h = clipRect.h * scale.y;

    if (SDL_RenderCopyEx(instance.GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0)
    {
        std::cout << "Fail to render the texture: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

int Sprite::GetHeight()
{
    return height * scale.y;
}

int Sprite::GetWidth()
{
    return (width / frameCount) * scale.x;
}

bool Sprite::IsOpen()
{

    return (texture != nullptr);
}

void Sprite::Update(float dt)
{
    if (frameCount != 1)
    {
        timeElapsed += dt;

        if (timeElapsed > frameTime)
        {

            timeElapsed = 0;
            if (currentFrame < frameCount - 1)
                currentFrame = currentFrame + 1;
        }
        SetClip((width / frameCount) * currentFrame, clipRect.y, width / frameCount, height);
    }
    if (secondsToSelfDestruct > 0)
    {
        selfDestructCount.Update(dt);
        if (selfDestructCount.Get() > secondsToSelfDestruct)
        {
            associated.RequestDelete();
        }
    }
}

bool Sprite::Is(string type)
{
    // Return true if the type wanted is Sprite
    return (type == "Sprite");
}
void Sprite::SetScaleX(float scaleX, float scaleY)
{
    Vec2 newScale = Vec2(scaleX, scaleY);
    if (newScale > Vec2(0, 0))
        scale = newScale;
}
Vec2 Sprite::GetScale()
{
    return scale;
}
void Sprite::SetFrame(int frame)
{
    currentFrame = frame;
    SetClip((width / frameCount) * currentFrame, clipRect.y, width / frameCount, height);
}

void Sprite::SetFrameCount(int frameCount)
{
    if (frameCount > 0)
    {
        this->frameCount = frameCount;

        associated.box.w = width / frameCount;
        SetClip((width / frameCount) * currentFrame, clipRect.y, width / frameCount, height);
    }
}

void Sprite::SetFrameTime(float frameTime)
{
    this->frameTime = frameTime;
    timeElapsed = 0;
}
