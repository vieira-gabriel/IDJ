#ifndef MINION_H
#define MINION_H

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"

#define MINION_AGULAR_VEL 20.0 * PI / 180

class Minion : public Component
{
private:
    GameObject &alienCenter;
    float arc;

public:
    Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg);

    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot(Vec2 target);
};

#endif