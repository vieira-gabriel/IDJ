#include <State.h>

State::State(/* args */)
{
    quitRequested = false;
    bg //instanciar depois
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
    //Not done
}