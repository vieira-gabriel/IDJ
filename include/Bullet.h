#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include <string>

using namespace std;

class Bullet : public Component
{
private:
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite);

    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();
};
