#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated) // Construct Component with the same associated that the Sound constructor receives
{
    // Atribute null pinter to chunk
    chunk = nullptr;
}

Sound::Sound(GameObject &associated, string file) : Sound(associated)
{
    // Open fle sound file
    Open(file);
}

Sound::~Sound()
{
    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times = 1)
{
    channel = Mix_PlayChannel(-1, chunk, 1);
}

void Sound::Stop()
{
    if (chunk != nullptr)
        Mix_HaltChannel(channel);
}
void Sound::Open(string file)
{
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr)
    {
        std::cout << "Unable to load WAV: " << SDL_GetError() << std::endl;
        exit(1);
    }
}
bool Sound::IsOpen()
{
    bool ret = (chunk != nullptr) ? true : false;
    return ret;
}
void Sound::Update(float dt)
{
}
void Sound::Render()
{
}
bool Sound::Is(string type)
{
    // Return true if the type wanted is Sound
    bool ret = (type == "Sound") ? true : false;
    return ret;
}