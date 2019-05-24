#include "Game.h"
#include "Resources.h"

Game *Game::instance = nullptr;

Game::Game(string title, int width, int height)
{
    storedState = nullptr;
    dt = 0;
    frameStart = SDL_GetTicks();

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

    if (TTF_Init() == 1)
    {
        std::cout << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
        exit(1);
    }

    std::cout << "TTF initialized" << std::endl;

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
    if (storedState != nullptr)
        delete storedState;

    while (!stateStack.empty())
        stateStack.pop();

    Resources::ClearImages();
    Resources::ClearSounds();
    Resources::ClearMusics();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
}

Game &Game::GetInstance()
{
    if (instance == nullptr)
        instance = new Game("Gabriel Vieira de Arimatéa 150126956", 1024, 600);

    return *instance;
}

State &Game::GetCurrentState()
{
    return *stateStack.top();
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

void Game::Push(State *state)
{
    storedState = state;
}

void Game::Run()
{
    std::cout << "Start running" << std::endl;

    // Load initial state
    if (storedState != nullptr)
    {
        stateStack.emplace(storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    }
    else
        return;

    InputManager &IM = InputManager::GetInstance();

    while (!stateStack.top()->QuitRequested())
    {
        if (storedState != nullptr)
        {
            if (!stateStack.empty())
                stateStack.top()->Pause();

            else
                break;
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }

        if (stateStack.top()->PopRequested())
        {
            stateStack.pop();

            Resources::ClearImages();
            Resources::ClearSounds();
            Resources::ClearMusics();

            if (!stateStack.empty())
            {
                stateStack.top()->Resume();
            }
        }

        CalculateDeltaTime();
        IM.Update();
        stateStack.top()->Update(dt);
        stateStack.top()->Render();

        SDL_RenderPresent(Game::GetInstance().GetRenderer());
        SDL_Delay(33);
    }

    while (!stateStack.empty())
        stateStack.pop();

    Resources::ClearImages();
    Resources::ClearSounds();
    // Resources::ClearMusics();
}

void Game::CalculateDeltaTime()
{
    dt = ((float)SDL_GetTicks() - (float)frameStart) / 1000;
    frameStart = SDL_GetTicks(); // Update frameStart
}

float Game::GetDeltaTime()
{
    return dt;
}