#include <State.h>

#define BACKGROUND_SPRITE "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC "assets/audio/stageState.ogg"

State::State() : bg(BACKGROUND_SPRITE), music(BACKGROUND_MUSIC)
{
    quitRequested = false;
    //LoadAssets();
    music.Play(-1);
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
    music.Open(BACKGROUND_MUSIC);
}

void State::Update(float dt)
{
    quitRequested = (SDL_QuitRequested() == true) ? true : false;

    SDL_Delay(dt);
}

void State::Render()
{
    bg.Render(0, 0);
}