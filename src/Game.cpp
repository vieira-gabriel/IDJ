#include <Game.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define CHUNKSIZE 1024
#define WINDOW_FLAG 0
#define RENDER_FLAG -1
#define AUDIO_CHANNELS 32

Game::Game(string title, int width, int height)
{
    if (instance != nullptr)
    {
        instance = this;
    }
    else
        ;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) == 0)
    {
        std::cout << "Unable to initialize Mix: " << Mix_GetError() << std::endl;
        exit(1);
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF); == 0)
    {
        std::cout << "Unable to initialize IMG: " << IMG_GetError() << std::endl;
        exit(1);
    }

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNKSIZE);

    Mix_AllocateChannels(AUDIO_CHANNELS);

    if (SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAG) == nullptr)
    {
        std::cout << "Unable to create window" << SDL_GetError() << std::endl;
        exit(1);
    }

    if (SDL_CreateRenderer(window, RENDER_FLAG, SDL_RENDERER_ACCELERATED) == nullptr)
    {
        std::cout << "Unable to create window" << SDL_GetError() << std::endl;
        exit(1);
    }
}

Game::~Game()
{
    delete state;
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
        instance = new Game("Penguin", 1024, 600);

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
    while (!State::state.quitRequest())
    {
        state.Update();
        state.Render();

        SDL_RenderPresent();

        SDL_Delay(33);
    }
}