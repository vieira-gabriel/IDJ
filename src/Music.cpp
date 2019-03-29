#include <Music.h>

Music::Music()
{
    music = nullptr;
}

Music::Music(string file)
{
    Open(file);
}

Music::~Music()
{
    Stop(1500);
    Mix_FreeMusic(music);
}

void Music::Play(int times = -1)
{
    if (IsOpen())
        Mix_PlayMusic(music, times);

    else
    {
        std::cout << "Error playing music" << std::endl;
        exit(1);
    }
}

void Music::Stop(int msToStop = 1500)
{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file)
{
    if (Mix_LoadMUS(file.c_str()) == nullptr)
    {
        std::cout << "Error opening music" << std::endl;
        exit(1);
    }
}

bool Music::IsOpen()
{
    bool ret = (music != nullptr) ? true : false;
    return ret;
}