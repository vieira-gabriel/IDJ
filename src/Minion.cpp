#include "Minion.h"

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated)
{
    Sprite *minion = new Sprite(associated, MINION_SOURCE);
    Collider *coliderBox = new Collider(associated);

    associated.AddComponent(coliderBox);

    float scale = (float(rand() % 50 + 1) / 100.0) + 1.0;
    minion->SetScaleX(scale, scale);

    associated.AddComponent(minion);

    arc = arcOffsetDeg * (PI / 180);

    this->alienCenter = alienCenter;
    shared_ptr<GameObject> shared_alienCenter = alienCenter.lock();

    Vec2 distance = Vec2(200, 0);

    if (shared_alienCenter != nullptr) // If Alien is not dead
    {
        distance.GetRotated(arc); // Rotates minion around the Alien

        distance += shared_alienCenter->box.CenterPoint(); // Sets distance to move
        distance.x -= associated.box.w / 2;
        distance.y -= associated.box.h / 2;

        associated.box.x = distance.x + shared_alienCenter->box.CenterPoint().x; // Moves minion to distance in x axis calculated
        associated.box.y = distance.y + shared_alienCenter->box.CenterPoint().x; // Moves minion to distance in y axis calculated
    }
    else
        associated.RequestDelete();
}

void Minion::Update(float dt)
{
    shared_ptr<GameObject> shared_alienCenter = alienCenter.lock();
    Vec2 distance = Vec2(200, 0);

    if (shared_alienCenter != nullptr) // If Alien is not dead
    {
        associated.angleDeg = arc * (180 / PI);
        distance.GetRotated(arc); // Rotates minion around the Alien

        distance += shared_alienCenter->box.CenterPoint();
        distance.x -= associated.box.w / 2;
        distance.y -= associated.box.h / 2;

        associated.box.x = distance.x; // Moves minion to distance in x axis calculated
        associated.box.y = distance.y; // Moves minion to distance in y axis calculated

        arc += MINION_AGULAR_VEL * dt; // Updates arc
    }
    else
    {
        associated.RequestDelete();
        GameObject *death = new GameObject();
        std::weak_ptr<GameObject> weak_ptr = Game::GetInstance().GetCurrentState().AddObject(death);
        std::shared_ptr<GameObject> ptr = weak_ptr.lock();

        Sprite *death_sprite = new Sprite(*ptr, ALIEN_DEATH_SRC, ALIEN_DEATH_FRAME, ALIEN_DEATH_FM_TIME, ALIEN_DEATH_SF_DEST);
        ptr->box = associated.box;
        ptr->AddComponent(death_sprite);
    }
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
    GameObject *bullet_GO = new GameObject;
    weak_ptr<GameObject> weak_bullet = Game::GetInstance().GetCurrentState().AddObject(bullet_GO);
    shared_ptr<GameObject> shared_bullet = weak_bullet.lock();

    float angle = (target - associated.box.CenterPoint()).Inclination();

    Bullet *bullet = new Bullet(*shared_bullet, angle, MINION_BULLET_SPEED, MINION_BULLET_DAMAGE, MINION_BULLET_DISTANCE, MINION_BULLET_SOURCE, M_BULLET_FRAMES, M_BULLET_FM_TIME, true);

    shared_bullet->box += associated.box.CenterPoint();

    shared_bullet->AddComponent(bullet);
}