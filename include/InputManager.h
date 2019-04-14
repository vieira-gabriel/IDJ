#ifndef IMPUT_MANAGER_H
#define IMPUT_MANAGER_H

class InputManager
{
private:
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