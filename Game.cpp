#include <Game.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

Game::Game(string title, int width, int height)
{
    if (instance != nullptr)
    {
        instance = this->instance;
    }
    else
        ;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game()
{
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
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

        SDL_RenderPresent(Game::GetInstance().GetRenderer());

        SDL_Delay(33);
    }
}