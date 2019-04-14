#ifndef IMPUT_MANAGER_H
#define IMPUT_MANAGER_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class InputManager
{
private:
    bool mouseState[6];
    int mouseUpdate[6];
    
    unordered_map<int, bool> keyState;
    unordered_map<int, bool> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;

    InputManager();
    ~InputManager();

public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMourseX();
    int GetMourseY();

    bool QuitRequested();

    static InputManager &GetInstance();
};

#endif