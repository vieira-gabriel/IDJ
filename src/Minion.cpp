#include "Minion.h"

#define MINION_SOURCE "assets/img/minion.png"

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(*new GameObject())
{
    Sprite *minion = new Sprite(associated, MINION_SOURCE);

    associated.AddComponent(minion);

    arc = arcOffsetDeg * (PI / 180);
    shared_ptr<GameObject> shared_alienCenter = alienCenter.lock();
    this->alienCenter = *shared_alienCenter;

    // Vec2 distance(200, 0);

    if (shared_alienCenter != nullptr)
    {
        // distance.GetRotated(arc);

        // distance += shared_alienCenter->box.CenterPoint();
        // distance.x -= associated.box.w / 2;
        // distance.y -= associated.box.h / 2;

        // associated.box += distance;
    }
    else
        associated.RequestDelete();
}

void Minion::Update(float dt)
{
    shared_ptr<GameObject> CenterAlien = make_shared<GameObject>(alienCenter);

    cout << "CenterAlien" << CenterAlien << endl;

    Vec2 distance = Vec2(200, 0);

    if (CenterAlien != nullptr) // If Alien is not dead
    {
        distance.GetRotated(arc); // Rotates minion around the Alien

        distance += CenterAlien->box.CenterPoint(); // Sets distance to move
        distance.x -= associated.box.w / 2;
        distance.y -= associated.box.h / 2;

        associated.box.x = distance.x; // Moves minion to distance in x axis calculated
        associated.box.y = distance.y; // Moves minion to distance in y axis calculated

        arc += MINION_AGULAR_VEL * dt; // Updates arc
    }
    else
        associated.RequestDelete();
}

void Minion::Render()
{
}

bool Minion::Is(string type)
{
    return (type == "Minion");
}

void Minion::Shoot(Vec2 target)
{
}
