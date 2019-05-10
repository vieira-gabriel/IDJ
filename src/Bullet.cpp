#include "Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated)
{
    Sprite *bullet_sprite = new Sprite(associated, sprite);
    this->damage = damage;
    distanceLeft = maxDistance;

    this->speed.x = speed;
    this->speed.y = 0; // Set a vector of speed on 0 degrees

    float arc = angle * (PI / 180);
    this->speed.GetRotated(arc); // Rotate the bullet, so it goes on the desired angle
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
