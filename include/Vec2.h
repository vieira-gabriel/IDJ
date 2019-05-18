#pragma once

#include <math.h>
#include "Rect.h"

#define PI 3.14159265

class Rect;

class Vec2
{
public:
  float x;
  float y;

  Vec2();
  Vec2(float xInit, float yInit);
  ~Vec2();

  Vec2 Sum(Vec2 vector);
  Vec2 Sub(Vec2 vector);
  Vec2 Mul(float m);
  float Mag();
  Vec2 Normalize();
  //Inclinação de um vetor em relação ao eixo x
  float Inclination();
  Vec2 GetRotated(float angle);
  float DistanceTo(Vec2 vector);
  Vec2 operator+(const Vec2 &vector);
  Vec2 operator-(const Vec2 &vector);
  Vec2 operator-();
  Vec2 operator*(const float scalar);
  Vec2 operator/(const float scalar);
  float operator*(const Vec2 &vector);
  bool operator>(const Vec2 &vector);
  bool operator<(const Vec2 &vector);
  void operator=(const Vec2 &vector);
  void operator-=(const Vec2 &vector);
  void operator+=(const Vec2 &vector);
  Rect operator+(const Rect &rect);
  Rect operator-(const Rect &rect);
  Vec2 operator*(const float rhs) const;
};