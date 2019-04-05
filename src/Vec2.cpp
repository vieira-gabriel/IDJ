#include "Vec2.h"

Vec2::Vec2()
{
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(float xInit, float yInit)
{
    this->x = xInit;
    this->y = yInit;
}

Vec2::~Vec2()
{
}

Vec2 Vec2::operator+(const Vec2 &vector)
{
    Vec2 result;
    result.x = this->x + vector.x;
    result.y = this->y + vector.y;
    return result;
}

Vec2 Vec2::Sum(Vec2 vector)
{
    Vec2 result;
    result.x = this->x + vector.x;
    result.y = this->y + vector.y;

    return result;
}

Vec2 Vec2::Sub(Vec2 vector)
{
    Vec2 result;
    result.x = this->x - vector.x;
    result.y = this->y - vector.y;

    return result;
}

Vec2 Vec2::Mul(float m)
{
    Vec2 result;
    result.x = this->x * m;
    result.y = this->y * m;

    return result;
}

float Vec2::Mag()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::Normalize()
{
    Vec2 result;

    float angle = asin(y / Mag());

    result.x = cos(angle);
    result.y = sin(angle);

    return result;
}

//Inclinação de um vetor em relação ao eixo x

Vec2 Vec2::GetRotated(float angle)
{
    float oldX = this->x;
    float oldY = this->y;
    this->x = (oldX * cos(angle)) - (oldY * sin(angle));
    this->y = (oldY * cos(angle)) + (oldX * sin(angle));

    return *this;
}