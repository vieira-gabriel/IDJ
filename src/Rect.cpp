#include "Rect.h"

Rect::Rect()
{
}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect::~Rect()
{
}

float Rect::Inclination(Rect rect)
{
    return atan2(rect.x - this->x, rect.y - this->y);
}

bool Rect::Contains(float valx, float valy)
{
    if (valx >= x && valx <= (x + w) && valy >= y && valy <= (y + h))
        return true;

    return false;
}

void Rect::SetCenter(Vec2 center)
{
    this->x = center.x - (this->w / 2.0);
    this->y = center.y - (this->h / 2.0);
}

Vec2 Rect::CenterPoint()
{
    return Vec2(x + w / 2.0, y + h / 2.0);
}

Rect Rect::operator+(const Vec2 &vector)
{

    return Rect(this->x + vector.x, this->y + vector.y, this->w, this->h);
}

Rect Rect::operator-(const Vec2 &vector)
{

    return Rect(this->x - vector.x, this->y - vector.y, this->w, this->h);
}

Rect Rect::operator*(const Vec2 &vector)
{
    return Rect(this->x, this->y, this->w * vector.x, this->h * vector.y);
}

void Rect::operator+=(const Vec2 &vector)
{

    this->x += vector.x;
    this->y += vector.y;
}

void Rect::operator+=(const Rect &rect)
{

    this->x += rect.x;
    this->y += rect.y;
}

void Rect::operator-=(const Vec2 &vector)
{

    this->x -= vector.x;
    this->y -= vector.y;
}

void Rect::operator=(const Rect &rect)
{

    this->x = rect.x;
    this->y = rect.y;
    this->w = rect.w;
    this->h = rect.h;
}