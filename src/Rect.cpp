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

float Rect::Inclination(Rect point1, Rect point2)
{
}

bool Rect::Contains(float valx, float valy)
{
    if (valx >= x && valx <= (x + w) && valy >= y && valy <= (y + h))
        return true;

    return false;
}
