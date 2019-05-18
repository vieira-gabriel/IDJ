#pragma once

#include "Component.h"
#include "Sprite.h"
#include "Game.h"
#include "Timer.h"

#define CANNON_SOURCE "assets/img/cubngun.png"
#define PENGUIN_BULLET_SPEED 200
#define PENGUIN_BULLET_DAMAGE 10
#define PENGUIN_BULLET_DISTANCE 1000
#define PENGUIN_BULLET_SOURCE "assets/img/penguinbullet.png"
#define COOLDOWN 0.5

#define P_BULLET_FRAMES 4
#define P_BULLET_FM_TIME 0.8

class PenguinCannon : public Component
{
private:
    weak_ptr<GameObject> pbody;
    float angle;

public:
    PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);
    ~PenguinCannon();

    void Update(float dt);
    void Render();
    bool Is(string type);

    void Shoot();
};
