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

float Vec2::Inclination()
{ //angle between vector and +x axis

    return atan2(y, x) * 180 / PI;
}

float Vec2::DistanceTo(Vec2 vector)
{

    float del_x = this->x - vector.x;
    float del_y = this->y - vector.y;

    return sqrt(del_x * del_x + del_y * del_y);
}

Vec2 Vec2::operator+(const Vec2 &vector)
{
    Vec2 result;
    result.x = this->x + vector.x;
    result.y = this->y + vector.y;
    return result;
}

Vec2 Vec2::operator-(const Vec2 &vector)
{

    return Vec2(this->x - vector.x, this->y - vector.y);
}

Vec2 Vec2::operator-()
{

    return (Vec2(-this->x, -this->y));
}

Vec2 Vec2::operator*(const float scalar)
{

    return Vec2(this->x * scalar, this->y * scalar);
}

bool Vec2::operator>(const Vec2 &vector)
{

    return (this->x > vector.x) && (this->y > vector.y);
}

bool Vec2::operator<(const Vec2 &vector)
{

    return (this->x < vector.x) && (this->y < vector.y);
}

void Vec2::operator=(const Vec2 &vector)
{

    this->x = vector.x;
    this->y = vector.y;
}

void Vec2::operator-=(const Vec2 &vector)
{

    this->x -= vector.x;
    this->y -= vector.y;
}

void Vec2::operator+=(const Vec2 &vector)
{

    this->x += vector.x;
    this->y += vector.y;
}

Rect Vec2::operator+(const Rect &rect)
{

    return Rect(this->x + rect.x, this->y + rect.y, rect.w, rect.h);
}

Rect Vec2::operator-(const Rect &rect)
{

    return Rect(this->x - rect.x, this->y - rect.y, rect.w, rect.h);
}