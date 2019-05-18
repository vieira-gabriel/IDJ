#include "Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated)
{
    Sprite *bullet = new Sprite(associated, sprite, frameCount, frameTime);
    Collider *coliderBox = new Collider(associated);

    associated.AddComponent(bullet);
    associated.AddComponent(coliderBox);

    associated.angleDeg = angle;

    this->damage = damage;
    distanceLeft = maxDistance;

    float rad_angle = angle * (PI / 180);
    this->speed = Vec2(speed * cos(rad_angle), speed * sin(rad_angle));
    this->targetsPlayer = targetsPlayer;
}

void Bullet::Update(float dt)
{
    associated.box += speed * dt;
    distanceLeft -= (speed * dt).Mag();

    if (distanceLeft <= 0)
        associated.RequestDelete();
}

void Bullet::Render()
{
}

bool Bullet::Is(string type)
{
    return (type == "Bullet");
}

int Bullet::GetDamage()
{
    return damage;
}

void Bullet::NotifyCollision(GameObject &other)
{
    if (other.GetComponent("Alien") != nullptr && !targetsPlayer)
        associated.RequestDelete();
    else if (other.GetComponent("PenguinBody") != nullptr && targetsPlayer)
        associated.RequestDelete();
}