#pragma once

#include "Component.h"

// #define DEBUG
#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

class Collider : public Component
{
private:
    Vec2 scale;
    Vec2 offset;

public:
    Rect box;

    Collider(GameObject &associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    void Update(float dt);
    void Render();
    bool Is(string type);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
};