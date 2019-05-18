#pragma once

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"

#define MINION_AGULAR_VEL 20.0 * PI / 180
#define MINION_BULLET_DAMAGE 5
#define MINION_BULLET_SPEED 200
#define MINION_BULLET_DISTANCE 1000

#define MINION_SOURCE "assets/img/minion.png"
#define MINION_BULLET_SOURCE "assets/img/minionbullet2.png"

#define M_BULLET_FRAMES 3
#define M_BULLET_FM_TIME 0.5

class Minion : public Component
{
private:
    weak_ptr<GameObject> alienCenter;
    float arc;

public:
    Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg);

    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot(Vec2 target);
};