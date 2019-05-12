#include "Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated)
{
    Sprite *bullet = new Sprite(associated, sprite);
    associated.AddComponent(bullet);

    associated.angleDeg = angle;

    this->damage = damage;
    distanceLeft = maxDistance;

    float rad_angle = angle * (PI / 180);
    this->speed = Vec2(speed * cos(rad_angle), speed * sin(rad_angle));
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
