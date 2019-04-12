#include <Music.h>
#include "Resources.h"

Music::Music()
{
    music = nullptr;
}

Music::Music(string file)
{
    music = nullptr;
    Open(file);
}

Music::~Music()
{
    Stop(1500);
    Mix_FreeMusic(music);
}

void Music::Play(int times = -1)
{
    if (music != nullptr)
    {
        if (Mix_PlayMusic(music, times) == -1)
        {
            std::cout << "Error playing music: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }
    else
    {
        std::cout << "No music loaded" << std::endl;
    }
}

void Music::Stop(int msToStop = 1500)
{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file)
{
    music = Resources::GetMusic(file);
}

bool Music::IsOpen()
{
    bool ret = (music != nullptr) ? true : false;
    return ret;
}