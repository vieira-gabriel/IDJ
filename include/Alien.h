#pragma once

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"
#include "Collider.h"
#include <queue>
#include <cstdlib>
#include <iostream>
#include <cmath>

#define ALIEN_HP 100
#define ALIEN_SPEED 150
#define ALIEN_ANGLE 20
#define ALIEN_SOURCE "assets/img/alien.png"
#define DISTANCE_ERROR 2

#define ALIEN_DEATH_SRC "assets/img/aliendeath.png"
#define ALIEN_DEATH_FRAME 4
#define ALIEN_DEATH_FM_TIME 0.3
#define ALIEN_DEATH_SF_DEST ALIEN_DEATH_FRAME *ALIEN_DEATH_FM_TIME
#define ALIEN_DEATH_SOUND_SRC "assets/audio/boom.wav"

#define ALIEN_REST 2
#define SHOOT_COOLDOWN 0.8

class Alien : public Component
{
private:
    Vec2 speed;
    int hp;
    vector<weak_ptr<GameObject>> minionArray;
    int nMinions;

    enum AlienState
    {
        MOVING,
        RESTING
    };

    AlienState state;
    Timer restTime;
    Timer shootTime;
    Vec2 destination;

public:
    static int alienCount;

    Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);
};
