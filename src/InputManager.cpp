#include "InputManager.h"

#define PI 3.14159265
#define QUIT SDL_QUIT
#define CLICK_MOUSE_DOWN SDL_MOUSEBUTTONDOWN
#define CLICK_MOUSE_UP SDL_MOUSEBUTTONUP
#define KEY_DOWN SDL_KEYDOWN
#define KEY_UP SDL_KEYUP

InputManager::InputManager()
{
    mouseState[6] = {};
    mouseUpdate[6] = {};
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
    SDL_Event event;
    updateCounter++;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    quitRequested = false;

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event))
    {
        if (!event.key.repeat)
        {
            // Se o evento for quit, setar a flag para terminação
            if (event.type == QUIT)
            {
                quitRequested = true;
            }

            // Se o evento for clique do mouse
            else if (event.type == CLICK_MOUSE_DOWN)
            {
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
            }

            // Se o evento for soltar clique do mouse
            else if (event.type == CLICK_MOUSE_UP)
            {
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
            }
            // Se o evento fot apertar tecla
            else if (event.type == KEY_DOWN)
            {
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
            // Se o evento for soltar tecla
            else if (event.type == KEY_UP)
            {
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
        }
    }
}

bool InputManager::KeyPress(int key)
{
    return (IsKeyDown(key) && (keyUpdate[key] == updateCounter)) ? true : false;
}

bool InputManager::KeyRelease(int key)
{
    return (!IsKeyDown(key) && (keyUpdate[key] == updateCounter)) ? true : false;
}

bool InputManager::IsKeyDown(int key)
{
    return keyState[key] ? true : false;
}

bool InputManager::MousePress(int button)
{
    return (IsMouseDown(button) && (mouseUpdate[button] == updateCounter)) ? true : false;
}

bool InputManager::MouseRelease(int button)
{
    return (!IsMouseDown(button) && (mouseUpdate[button] == updateCounter)) ? true : false;
}

bool InputManager::IsMouseDown(int button)
{
    return mouseState[button] ? true : false;
}

int InputManager::GetMourseX()
{
    return mouseX;
}

int InputManager::GetMourseY()
{
    return mouseY;
}

bool InputManager::QuitRequested()
{
    return quitRequested;
}

InputManager &InputManager::GetInstance()
{
    static InputManager IM;
    return IM;
}
