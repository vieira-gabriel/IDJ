#include "Resources.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;

unordered_map<string, shared_ptr<SDL_Texture>>::iterator itTexture;
unordered_map<string, shared_ptr<Mix_Music>>::iterator itMusic;
unordered_map<string, shared_ptr<Mix_Chunk>>::iterator itChunk;
unordered_map<string, shared_ptr<TTF_Font>>::iterator itFont;

shared_ptr<SDL_Texture> Resources::GetImage(string file)
{
    itTexture = imageTable.find(file.c_str());

    if (itTexture != imageTable.end())
        return itTexture->second;

    SDL_Renderer *render = Game::GetInstance().GetRenderer();
    SDL_Texture *texture = IMG_LoadTexture(render, file.c_str());

    if (texture == nullptr)
    {
        std::cout << "Fail to load texture " << file << "; " << SDL_GetError() << std::endl;
        exit(1);
    }

    shared_ptr<SDL_Texture> s_txtr(texture, [](SDL_Texture *texture) { SDL_DestroyTexture(texture); }); //Aggregate initialization
    imageTable[file.c_str()] = s_txtr;
    return imageTable[file.c_str()];
}

void Resources::ClearImages()
{
    for (itTexture = imageTable.begin(); itTexture != imageTable.end(); itTexture++)
    {
        if (itTexture->second.unique())
            itTexture = imageTable.erase(itTexture);
    }

    imageTable.clear();
}

shared_ptr<Mix_Music> Resources::GetMusic(string file)
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

    shared_ptr<Mix_Music> sharedMusic(music, [](Mix_Music *music) { Mix_FreeMusic(music); }); //Aggregate initialization

    musicTable[file.c_str()] = sharedMusic;
    return sharedMusic;
}

void Resources::ClearMusics()
{
    for (itMusic = musicTable.begin(); itMusic != musicTable.end(); itMusic++)
    {
        if (itMusic->second.unique())
            itMusic = musicTable.erase(itMusic);
    }

    musicTable.clear();
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file)
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

    shared_ptr<Mix_Chunk> sharedChunk(chunk, [](Mix_Chunk *sound) { Mix_FreeChunk(sound); }); //Aggregate initialization
    soundTable[file] = sharedChunk;
    return sharedChunk;
}

void Resources::ClearSounds()
{
    for (itChunk = soundTable.begin(); itChunk != soundTable.end(); itChunk++)
    {
        if (itChunk->second.unique())
            itChunk = soundTable.erase(itChunk);
    }

    soundTable.clear();
}

shared_ptr<TTF_Font> Resources::GetFont(string file, int fontSize)
{
    TTF_Font *font;

    string extFile = file + to_string(fontSize);
    itFont = fontTable.find(extFile.c_str());

    if (itFont != fontTable.end())
        return itFont->second;

    font = TTF_OpenFont(file.c_str(), fontSize);

    if (font == nullptr)
    {
        std::cout << "Error opening font " << file << std::endl;
        exit(1);
    }

    shared_ptr<TTF_Font> sharedFont(font, [](TTF_Font *font) { TTF_CloseFont(font); }); //Aggregate initialization
    fontTable[extFile] = sharedFont;
    return sharedFont;
}

void Resources::ClearFont()
{
    for (itFont = fontTable.begin(); itFont != fontTable.end(); itFont++)
    {
        if (itFont->second.unique())
            itFont = fontTable.erase(itFont);
    }

    fontTable.clear();
}
