#pragma once

#include "Component.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"

#define PENGUIN_BODY_SOURCE "assets/img/penguin.png"
#define PENGUIN_HP 100
#define PENGUIN_ACCELERATION 60.0
#define PENGUIN_ANGULAR_VEL 80.0 * (PI / 180.0)
#define MAXIMUM_SPEED_MOD 300.0

#define PENGUIN_DEATH_SRC "assets/img/penguindeath.png"
#define PENGUIN_DEATH_FRAME 5
#define PENGUIN_DEATH_FM_TIME 0.3
#define PENGUIN_DEATH_SF_DEST PENGUIN_DEATH_FRAME *PENGUIN_DEATH_FM_TIME
#define PENGUIN_DEATH_SOUND_SRC "assets/audio/boom.wav"

class PenguinBody : public Component
{
private:
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

public:
    static PenguinBody *player;

    PenguinBody(GameObject &associated);
    ~PenguinBody();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);
    Vec2 PenguinAt();
};
