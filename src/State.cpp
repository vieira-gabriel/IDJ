#include <State.h>

#define BACKGROUND_SPRITE "assets/img/ocean.jpg"

State::State(/* args */)
{
    quitRequested = false;
    LoadAssets();
}

State::~State()
{
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::LoadAssets()
{
    bg.Open(BACKGROUND_SPRITE);
}

void State::Update(float dt)
{
    quitRequested = SDL_QuitRequested() == true ? true : false;
    SDL_Delay(dt);
}

void State::Render()
{
    bg.Render(0, 0);
}