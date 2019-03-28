#include <State.h>

State::State(/* args */)
{
    quitRequested = false;
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
}

void State::Update(float dt)
{
    quitRequested = SDL_QuitRequested() == true ? true : false;
}

void State::Render()
{
    bg.Render(0, 0);
}