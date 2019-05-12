#pragma once

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"
#include <queue>
#include <cstdlib>
#include <iostream>
#include <cmath>

#define ALIEN_HP 100
#define ALIEN_SPEED 150
#define ALIEN_ANGLE 20

class Alien : public Component
{
private:
    class Action
    {
    public:
        enum ActionType
        {
            MOVE,
            SHOOT
        };
        ActionType type;
        Vec2 pos;

        Action(ActionType type, float x, float y);
    };

    Vec2 speed;
    int hp;
    queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;
    int nMinions;

public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
};
