#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include <string>

using namespace std;

class Bullet : public Component
{
private:
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    bool targetsPlayer;

    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer);

    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();
    void NotifyCollision(GameObject &other);
};
