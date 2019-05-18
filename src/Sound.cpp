#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject &associated) : Component(associated) // Construct Component with the same associated that the Sound constructor receives
{
    // Atribute null pinter to chunk
    chunk = nullptr;
    channel = -2;
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
        // Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times = 1)
{
    if (times > 0)
        times -= 1;
    channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop()
{
    if (chunk != nullptr)
        Mix_HaltChannel(channel);
}
void Sound::Open(string file)
{
    chunk = Resources::GetSound(file.c_str());
    if (chunk == nullptr)
    {
        // Falha em carregar o som.
        std::cout << "Faile to load sound: " << file.c_str() << "\n";
        std::cout << "SDL_GetError: " << SDL_GetError() << "\n";
        //exit(EXIT_FAILURE);
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
    return (type == "Sound");
}