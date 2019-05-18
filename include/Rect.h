#pragma once

#include "Vec2.h"

class Vec2;

class Rect
{
public:
  float x;
  float y;
  float w;
  float h;

  Rect();
  Rect(float x, float y, float w, float h);
  ~Rect();
  float Inclination(Rect rect);
  bool Contains(float valx, float);
  void SetCenter(Vec2 center);
  Vec2 CenterPoint();
  Rect operator-(const Vec2 &vector);
  Rect operator+(const Vec2 &vector);
  Rect operator*(const Vec2 &vector);
  void operator+=(const Vec2 &vector);
  void operator+=(const Rect &rect);
  void operator-=(const Vec2 &vector);
  void operator=(const Rect &rect);
};