#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "InputManager.h"
#include <queue>
#include <cstdlib>
#include <iostream>

#define ALIEN_HP 100
#define ALIEN_SPEED 70

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

public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif