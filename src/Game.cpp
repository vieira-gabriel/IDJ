#include "Game.h"

#define CHUNKSIZE 1024
#define WINDOW_FLAG 0
#define AUDIO_CHANNELS 32

Game *Game::instance = nullptr;

Game::Game(string title, int width, int height)
{
    srand(time(NULL));
    if (instance != nullptr)
    {
        instance = this;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    std::cout << "SDL initialized" << std::endl;

    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) == 0)
    {
        std::cout << "Unable to initialize Mix: " << Mix_GetError() << std::endl;
        exit(1);
    }

    std::cout << "Mix initialized" << std::endl;

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
    {
        std::cout << "Unable to initialize IMG: " << IMG_GetError() << std::endl;
        exit(1);
    }

    std::cout << "IMG initialized" << std::endl;

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNKSIZE);

    std::cout << "Mix Audio opened" << std::endl;

    Mix_AllocateChannels(AUDIO_CHANNELS);

    std::cout << "Channels Allocated" << std::endl;

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAG);

    if (window == nullptr)
    {
        std::cout << "Unable to create window: " << SDL_GetError() << std::endl;
        exit(1);
    }

    std::cout << "Window created" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        std::cout << "Unable to create Renderer: " << SDL_GetError() << std::endl;
        exit(1);
    }

    std::cout << "Renderer created" << std::endl;
}

Game::~Game()
{
    //delete state;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

Game &Game::GetInstance()
{
    if (instance == nullptr)
        instance = new Game("Gabriel Vieira de Arimatéa 150126956", 1024, 600);

    return *instance;
}

State &Game::GetState()
{
    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

void Game::Run()
{
    std::cout << "Start running" << std::endl;

    state = new State;

    while (state->QuitRequested() != true)
    {
        state->Update(33);
        state->Render();

        SDL_RenderPresent(Game::GetInstance().GetRenderer());
    }
}