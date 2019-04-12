#include "Resources.h"

unordered_map<std::string, SDL_Texture *> Resources::imageTable;
unordered_map<std::string, Mix_Music *> Resources::musicTable;
unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

unordered_map<std::string, SDL_Texture *>::iterator itTexture;
unordered_map<std::string, Mix_Music *>::iterator itMusic;
unordered_map<std::string, Mix_Chunk *>::iterator itChunk;

SDL_Texture *Resources::GetImage(string file)
{
    itTexture = imageTable.find(file);

    if (itTexture != imageTable.end())
        return itTexture->second;

    SDL_Renderer *render = Game::GetInstance().GetRenderer();
    SDL_Texture *texture = IMG_LoadTexture(render, file.c_str());

    if (texture == nullptr)
    {
        std::cout << "Fail to load texture " << file << "; " << SDL_GetError() << std::endl;
        exit(1);
    }

    imageTable[file] = texture;
    return texture;
}

void Resources::ClearImages()
{
    for (itTexture = imageTable.begin(); itTexture != imageTable.end(); itTexture++)
    {
        if (itTexture->second != nullptr)
            SDL_DestroyTexture(itTexture->second);
    }

    imageTable.clear();
}

Mix_Music *Resources::GetMusic(string file)
{
    Mix_Music *music;

    itMusic = musicTable.find(file.c_str());

    if (itMusic != musicTable.end())
        return itMusic->second;

    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr)
    {
        std::cout << "Error opening music " << file << std::endl;
        exit(1);
    }

    musicTable[file] = music;
    return music;
}

void Resources::ClearMusics()
{
    for (itMusic = musicTable.begin(); itMusic != musicTable.end(); itMusic++)
    {
        if (itMusic->second != nullptr)
            Mix_FreeMusic(itMusic->second);
    }

    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(string file)
{
    Mix_Chunk *chunk;

    itChunk = soundTable.find(file.c_str());

    if (itChunk != soundTable.end())
        return itChunk->second;

    chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr)
    {
        std::cout << "Error opening chunk " << file << std::endl;
        exit(1);
    }

    soundTable[file] = chunk;
    return chunk;
}

void Resources::ClearSounds()
{
    for (itChunk = soundTable.begin(); itChunk != soundTable.end(); itChunk++)
    {
        if (itChunk->second != nullptr)
            Mix_FreeChunk(itChunk->second);
    }

    soundTable.clear();
}