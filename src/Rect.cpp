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

Vec2 Rect::CenterPoint()
{
    Vec2 center = Vec2(x + w / 2, y + h / 2);
    return center;
}

Rect Rect::operator+(const Vec2 &vec)
{ //sums rect with vec2 (moves rect along vec) and returns a new rect

    return Rect(this->x + vec.x, this->y + vec.y, this->w, this->h);
}

Rect Rect::operator-(const Vec2 &vec)
{ //subtracts rect with vec2 (moves rect along - vec) and returns a new rect

    return Rect(this->x - vec.x, this->y - vec.y, this->w, this->h);
}

void Rect::operator+=(const Vec2 &vec)
{ //sums rect with vec2 (moves rect along vec), moving it

    this->x += vec.x;
    this->y += vec.y;
}

void Rect::operator-=(const Vec2 &vec)
{ //subtracts rect with vec2 (moves rect along - vec), movint it

    this->x -= vec.x;
    this->y -= vec.y;
}

void Rect::operator=(const Rect &rec)
{ //assigns this rect to a given rect

    this->x = rec.x;
    this->y = rec.y;
    this->w = rec.w;
    this->h = rec.h;
}